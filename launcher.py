#!/usr/bin/env python3

# to use this launcher you must install websockets using pip:
#   pip3 install --user websockets
# on debian/ubuntu you may need:
#   sudo apt install python3-pip
#
# launch using
#   python3 launcher [-k/--keep-open] <sworms executable> [sworms args]

import asyncio
import sys, os
import traceback
from asyncio.subprocess import PIPE as PIPE

try:
  import websockets
except ModuleNotFoundError:
  print("you have to install websockets using pip (pip3 install --user websockets)", file=sys.stderr)
  sys.exit(1)

PROMPT = b"sep> "
HOST = 'localhost'
PORT = 8765

if len(sys.argv) >= 2 and (sys.argv[1] == '--keep-open' or sys.argv[1] == '-k'):
    keep_open = True
    sys.argv = sys.argv[:1] + sys.argv[2:]
else:
    keep_open = False

async def forwardstdin(ws, proc):
    try:
        while True:
            line = await ws.recv()
            print("< {}".format(line.strip()))
            proc.stdin.write((line + "\n").encode())
    except websockets.exceptions.ConnectionClosed:
        print("websocket closed")
        if proc.proc.returncode is None:
          proc.kill();
        if not keep_open:
          sys.exit(0)
    except Exception as e:
        print("< exception")
        traceback.print_exc()
        raise

async def forwardstdout(ws, proc):
    try:
        while True:
            resp = await proc.stdout.readuntil(PROMPT)
            resp = resp.decode()
            print("> '{}'".format(resp))
            sys.stdout.flush()
            await ws.send(resp)
    except asyncio.IncompleteReadError as e:
        retcode = await proc.wait()
        if e.partial != b"":
            print("partially read data: '{}'".format(e.partial.decode()))
            await ws.send(e.partial.decode())
        await ws.close()
        print("process exited with return code {}".format(retcode))
        if not keep_open:
          sys.exit(retcode)
    except websockets.exceptions.ConnectionClosed as e:
        print("websocket closed")
        if not keep_open:
          sys.exit(0)
    except Exception as e:
        print("> exception")
        traceback.print_exc()
        raise

async def run_sworms(websocket, path):
    prog = sys.argv[1]
    args = [x.encode() for x in sys.argv[2:]]
    print(prog, args)
    proc = await asyncio.create_subprocess_exec(prog, *args, stdin=PIPE, stdout=PIPE)
    print("connection on " + path)
    sipo = forwardstdin(websocket, proc)
    piso = forwardstdout(websocket, proc)
    await asyncio.wait([sipo, piso])

if len(sys.argv) < 2:
    print("usage: ./launcher [-k/--keep-open] <sworms executable> [sworms args]...", file=sys.stderr)
    sys.exit(1)

start_server = websockets.serve(run_sworms, HOST, PORT)

asyncio.get_event_loop().run_until_complete(start_server)
print("listening on ws://{}:{}".format(HOST, PORT))
asyncio.get_event_loop().run_forever()
