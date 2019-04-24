//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
//------------------------------------------------------------------------------
//

#include "Game.h"
#include "Worm.h"
#include "Chest.h"
#include "Random.h"
#include "Move.h"
#include "Help.h"
#include "State.h"
#include "Map.h"
#include "Action.h"
#include "Choose.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <vector>

#define CURRENT_FIELD ((row * board_width_) + col)
#define BELOW_CURRENT_FIELD ((row + 1) * board_width_ + col)
#define ABOVE_CURRENT_FIELD (((row - 1) * board_width_) + col)
#define TARGET_FIELD ((row * board_width_) + step_direction)
#define BELOW_TARGET_FIELD ((row + 1) * board_width_ + step_direction)
#define ABOVE_TARGET_FIELD (((row - 1) * board_width_) + step_direction)

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::string;
using std::map;
using std::pair;
using std::setw;
using std::vector;
using Sep::Game;
using Sep::Worm;

const string Game::MAGIC_VALUE = "#SWORMS";
const string Game::CHECK_FOR_SIZE = "SIZE:";
const string Game::CHECK_FOR_MAP = "MAP:";

const string Game::COMMAND_PROMPT = "sep> ";
const string Game::COMMAND_MOVE = "move";
const string Game::COMMAND_ACTION = "action";
const string Game::COMMAND_QUIT = "quit";
const string Game::COMMAND_HELP = "help";
const string Game::COMMAND_STATE = "state";
const string Game::COMMAND_MAP = "map";
const string Game::COMMAND_CHOOSE = "choose";


//------------------------------------------------------------------------------
Game::Game() : board_width_(0), board_height_(0), map_(), wormNumber()
{
  Game::map_.insert(pair<int, Field>(board_height_ * board_width_,
                                     Field(Field::AIR)));
}

//------------------------------------------------------------------------------
Game::ErrorType Game::printErrorMessage(ErrorType type)
{
  switch(type)
  {
    case INVALID_CONFIGFILE:
      cout << "[ERROR] invalid config file" << endl;
      break;
    case INVALID_TARGET:
      cout << "[ERROR] invalid target" << endl;
      break;
    case WRONG_MOVE:
      cout << "[WARNING] can't move further" << endl;
      break;
    case UNKNOWN_COMMAND:
      cout << "[ERROR] unknown command!" << endl;
      break;
    case WRONG_PARAMETER_COUNT:
      cout << "[ERROR] wrong parameter count!" << endl;
      break;
    case COMMAND_NOT_ALLOWED:
      cout << "[ERROR] command currently not allowed!" << endl;
          break;
    case EVERYTHING_OK:
      break;
  }
  return type;
}

//------------------------------------------------------------------------------
void Game::printDeathCases(DeathCases type, int current_worm)
{
  switch(type)
  {
    case DROWNED:
      cout << wormNumber.at(current_worm).getName() << " (" <<
           wormNumber.at(current_worm).getId() << ")" << " drowned." << endl;
      break;
    case FELL:
      cout << wormNumber.at(current_worm).getName() << " (" <<
           wormNumber.at(current_worm).getId() << ")" << " fell into his death."
           << endl;
      break;
    case OUTOFMAP:
      cout << wormNumber.at(current_worm).getName() << " (" <<
           wormNumber.at(current_worm).getId() << ")" << " fell out of the map."
           << endl;
      break;
    case DIED:
      cout << wormNumber.at(current_worm).getName() << " (" <<
           wormNumber.at(current_worm).getId() << ")" << " died." << endl;
      break;
  }
}

//------------------------------------------------------------------------------
int Game::loadConfig(string cfg_file)
{
  int row = 0;
  ConfigKeywords check = SIZE;
  stringstream size, map;
  string file_input, keyword;

  ifstream file(cfg_file);
  if(!file.is_open())
  {
    return printErrorMessage(INVALID_CONFIGFILE);
  }

  if(!(file >> file_input) || file_input != MAGIC_VALUE) //Checks #SWORMS
  {
    return printErrorMessage(INVALID_CONFIGFILE);
  }

  while(getline(file, file_input))
  {
    if((!file_input.empty()) && (file_input.at(0) != '#'))
    {
      if(check == SIZE) //Checks for SIZE:
      {
        size << file_input;
        size >> keyword >> board_width_ >> board_height_;
        check = MAP;
        if((CHECK_FOR_SIZE != keyword || (board_width_ < MIN_LENGTH
                                          || board_width_ > MAX_LENGTH) ||
            (board_height_ < MIN_LENGTH
             || board_height_ >
                MAX_LENGTH))) //Returns printError if the size of the
          // board  is too small or too big or the keyword SIZE was not found
        {
          return printErrorMessage(INVALID_CONFIGFILE);
        }
      }
      else if(check == MAP)
      {
        map << file_input;
        map >> keyword;
        check = MAPFIELDS;
        if((CHECK_FOR_MAP != keyword))
        {
          return printErrorMessage(INVALID_CONFIGFILE);
        }
      }
      else if(check == MAPFIELDS)
      {
        int length = static_cast<int>(file_input.length());
        if(length != board_width_ || !createMapFields(file_input, row))
        {
          return printErrorMessage(INVALID_CONFIGFILE);
        }
        row += board_width_;
      }
    }
  }
  file.close();
  return EVERYTHING_OK;
}

//------------------------------------------------------------------------------
bool Game::createMapFields(string keyword, int row)
{
  for(int index = 0; index < board_width_; index++)
  {
    if(keyword.at(index) == 'A'
       && row < ((board_height_ - ONE) * board_width_)) // Saves each field
      // type to a position in the map
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::AIR)));
    }
    else if(keyword.at(index) == 'E' && row != 0)
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::EARTH)));
    }
    else if(keyword.at(index) == 'W' && row != 0
            && row >= ((board_height_ - ONE) * board_width_))
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::WATER)));
    }
    else
    {
      return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
void Game::createWorms(Random *random)
{
  int col;
  int row = 0;

  for(int index = 1; index < 7; index++)
  {
    wormNumber.emplace_back(Worm(index, random->getWormName()));
  }
  for(int index = 1; index < 7; index++)
  {
    col = random->getRandomInt(0, board_width_ - 1);
    while((map_.at(BELOW_CURRENT_FIELD).getType() == Field::AIR
           && map_.at(CURRENT_FIELD).getType() == Field::AIR))
    {
      row++; // row gets increased to handle gravity
    }
    wormNumber.at(index - 1).setPosition(row, col);
    cout << "spawning " << wormNumber.at(index - 1).getName() << " ("
         << wormNumber.at(index - 1).getId() << ")" << " at " << "(0," << col
         << ")" << endl;

    if(map_.at(BELOW_CURRENT_FIELD).getType() == Field::WATER)
    {
      printDeathCases(DROWNED, (index - 1));
      wormNumber.at(index - 1).setHp(0);
    }
    else
    {
      map_.at(CURRENT_FIELD).setType(Field::WORM);
      wormNumber.at(index - 1).setHp(100);
    }
    row = 0;
  }
}

//------------------------------------------------------------------------------
void Game::createChest(Random *random)
{
  int weapon_number = random->getRandomInt(0, 4); // needs to be implemented
  int col = random->getRandomInt(0, board_width_ - 1);
  int row = 0;
  while((map_.at(BELOW_CURRENT_FIELD).getType() == Field::AIR
         && map_.at(CURRENT_FIELD).getType() == Field::AIR))
  {
    row++; // row gets increased to handle gravity
  }
  if(map_.at(BELOW_CURRENT_FIELD).getType() != Field::WATER)
  {
    map_.at(CURRENT_FIELD).setType(Field::CHEST); // adds Chest to the map
  }
}

//------------------------------------------------------------------------------
void Game::printMap()
{
  int count_to_ten = 0;
  cout << "Current Map:" << endl;
  for(int index_row = 0; index_row <= (board_height_ + 1); index_row++)
  {
    if(index_row == 0 || index_row == (board_height_ + 1))
    {
      cout << "  ";
    }
    else
    {
      cout << setw(MAX_DIGITS) << (index_row - 1);
    }
    for(int index_col = 0; index_col < board_width_; index_col++)
    {
      if(index_row == 0 || index_row == (board_height_ + 1))
      {
        if(count_to_ten == MIN_LENGTH)
        {
          count_to_ten = 0;
        }
        cout << count_to_ten;
        count_to_ten++;
      }
      else
      {
        if(map_.at(index_col + (index_row - 1) * board_width_).getType() !=
           Field::WORM)
        {
          cout << map_.at(
            index_col + (index_row - 1) * board_width_).getCharacter();
        }
        else
        {
          for(int count = 0; count < 6; count++)
          {
            if((index_col + (index_row - 1) * board_width_) ==
               (wormNumber.at(count).getCol() +
                wormNumber.at(count).getRow() * board_width_))
            {
              cout << wormNumber.at(count).getCharacter();
            }
          }
        }
        count_to_ten = 0;
      }
    }
    if(index_row == 0 || index_row == (board_height_ + 1))
    {
      cout << endl;
    }
    else
    {
      cout << setw(MAX_DIGITS) << (index_row - 1) << endl;
    }
  }
}

//------------------------------------------------------------------------------
int Game::gameLoop()
{
  int current_worm = 0;
  int player = 1;
  int move_command;


  int turn_one = 0;
  int turn_two = 3;

  Random random;
  createWorms(&random);
  printMap();

  while(true)
  {
    if(setPlayerAndWorm(current_worm, player, turn_one, turn_two))
    {
      return 0; //wormNumber.at(current_worm) makes next move
    }
    move_command = 0;
    while(!userInput(current_worm, move_command))
    {
    }
    createChest(&random); // adds chest on the end of every turn
  }
}

//------------------------------------------------------------------------------
int Game::setPlayerAndWorm(int &current_worm, int &player, int &turn_one,
                           int &turn_two)
{
  int check = 0;
  while(check++ < 3)
  {
    current_worm = 0;
    if(player % 2) // Player one
    {
      current_worm += turn_one++;
      if(turn_one > 2)
      {
        turn_one = 0;
      }
    }
    else // Player two
    {
      current_worm += turn_two++;
      if(turn_two > 5)
      {
        turn_two = 3;
      }
    }

    if(wormNumber.at(current_worm).getHp() != 0)
    {
      cout << "Player " << player;
      if(player % 2) // Player one
      {
        player = 2;
      }
      else
      {
        player = 1;
      }
      cout << " Worm " << wormNumber.at(current_worm).getName() <<
           " (" << wormNumber.at(current_worm).getId() << ") at " << "("
           << wormNumber.at(current_worm).getRow()
           << ", " << wormNumber.at(current_worm).getCol() << ") ready" << endl;
      return EVERYTHING_OK;
    }
  }
  return 1; // If one Player has no more accessible worms
}

//------------------------------------------------------------------------------
void Game::testWormTower(int &row, int &col, int &detect_worm_tower,
                         int current_worm)
{
  if(map_.at(ABOVE_CURRENT_FIELD).getType() == Field::WORM)
  {
    while(map_.at(ABOVE_CURRENT_FIELD).getType() == Field::WORM)
    {
      for(int index = 0; index < 6; index++)
      {
        if((wormNumber.at(index).getRow() * wormNumber.at(index).getCol())
           == ((wormNumber.at(current_worm).getRow() - 1) *
               wormNumber.at(current_worm).getCol()))
        {
          wormNumber.at(index).setPosition(row, col);
          current_worm = index;
        }
      }
      row--;// If a "worm tower" was found
    }
    map_.at(CURRENT_FIELD).setType(Field::AIR);

    row = detect_worm_tower;
  }
  else
  {
    map_.at(CURRENT_FIELD).setType(Field::AIR);
  }
}

//------------------------------------------------------------------------------
bool Game::checkDirection(int &steps)
{
  bool left_steps = false;
  if(steps < 0)
  {
    left_steps = true;
  }
  return left_steps;
}

//------------------------------------------------------------------------------
bool Game::makeMove(int &row, int &col, bool left_steps, int current_worm)
{
  int detect_worm_tower = row;
  int step_direction = (col + 1);
  if(left_steps)
  {
    step_direction = (col - 1); // left direction
  }
  if(step_direction >= board_width_ || step_direction < 0)
  {
    return false;
  }
  if((map_.at(ABOVE_CURRENT_FIELD).getType() != Field::EARTH)
     && ((map_.at(TARGET_FIELD).getType() == Field::WORM ||
          map_.at(TARGET_FIELD).getType() == Field::EARTH)
         &&
         map_.at(ABOVE_TARGET_FIELD).getType() == Field::AIR)) // Climb command
  {
    testWormTower(row, col, detect_worm_tower, current_worm);
    map_.at(ABOVE_TARGET_FIELD).setType(Field::WORM);
    wormNumber.at(current_worm).setPosition((row - 1), step_direction);
    row--;
    col = step_direction;
    return true;
  }
  if(map_.at(TARGET_FIELD).getType() == Field::AIR) // Step command
  {
    testWormTower(row, col, detect_worm_tower, current_worm);
    while((map_.at(BELOW_TARGET_FIELD).getType() == Field::AIR))
    {
      row++;
    }
    if(map_.at(BELOW_TARGET_FIELD).getType() == Field::EARTH
       || map_.at(BELOW_TARGET_FIELD).getType() == Field::WORM)
    {
      map_.at(TARGET_FIELD).setType(Field::WORM);
      wormNumber.at(current_worm).setPosition(row, step_direction);
      col = step_direction;
      return true;
    }
    else if(map_.at(BELOW_TARGET_FIELD).getType() == Field::CHEST)
    {
      map_.at(BELOW_TARGET_FIELD).setType(Field::WORM);
      wormNumber.at(current_worm).setPosition((row + 1), step_direction);
      return true;
    }
    else if(map_.at(BELOW_TARGET_FIELD).getType() == Field::WATER)
    {
      map_.at(BELOW_TARGET_FIELD).setType(Field::WORM);
      wormNumber.at(current_worm).setHp(0);
    }
  }
  return false;
}

//------------------------------------------------------------------------------
void Game::move(int row, int col, int steps, int current_worm)
{
  bool left_steps = checkDirection(steps);
  for(int index = 0; index < std::abs(steps); index++)
  {
    if(!makeMove(row, col, left_steps, current_worm))
    {
      if(wormNumber.at(current_worm).getHp() > 0)
      {
        printErrorMessage(WRONG_MOVE);
        break;
      }
      else
      {
        printDeathCases(DROWNED, current_worm);
        break;
      }
    }
  }
}

//------------------------------------------------------------------------------
vector<Worm> Game::getWormNumber()
{
  return wormNumber;
}

//------------------------------------------------------------------------------
bool Game::userInput(int current_worm, int &move_command)
{
  string input_line;
  string param;
  vector<string> command_params;

  cout << COMMAND_PROMPT;
  getline(cin, input_line);
  std::transform(input_line.begin(), input_line.end(), input_line.begin(), ::tolower);
  if(cin.eof())
  {
      exit(EVERYTHING_OK);
  }
  stringstream input_stream(input_line);
  while(input_stream >> param)
  {
    command_params.push_back(param);
  }
  if(command_params.empty())
  {
      return false;
  }
  if(command_params.size() > 3)
  {
      printErrorMessage(UNKNOWN_COMMAND);
      return false;
  }
  if(checkOneParameterCommand(command_params, current_worm, move_command))
  {
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool Game::checkOneParameterCommand(std::vector<std::string> command_params, int current_worm, int &move_command)
{
  if(command_params.size() == 1 && (command_params.at(0) != COMMAND_MOVE &&
          command_params.at(0) != COMMAND_CHOOSE && command_params.at(0) != COMMAND_ACTION))
  {
    if(command_params.at(0) == COMMAND_QUIT)
    {
      exit(EVERYTHING_OK);
    }
    else if(command_params.at(0) == COMMAND_HELP)
    {
      Help help(COMMAND_HELP);
      return help.execute(*this, command_params) == 0;
    }
    else if(command_params.at(0) == COMMAND_STATE)
    {
      State state(COMMAND_STATE, current_worm);
      return state.execute(*this, command_params) == 0;
    }
    else if(command_params.at(0) == COMMAND_MAP)
    {
      Map map(COMMAND_MAP);
      return map.execute(*this, command_params) == 0;
    }
    else
    {
      printErrorMessage(UNKNOWN_COMMAND);
      return true;
    }
  }
  else if(command_params.size() != 1 && (command_params.at(0) == COMMAND_QUIT
            || command_params.at(0) == COMMAND_HELP || command_params.at(0) == COMMAND_STATE
            || command_params.at(0) == COMMAND_MAP))
  {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return true;
  }
  else
  {
    if(checkMoreParameterCommand(command_params, current_worm, move_command))
    {
      return false;
    }
    return true;
  }
}


bool Game::checkMoreParameterCommand(std::vector<std::string> command_params, int current_worm, int &move_command)
{
  if(command_params.at(0) == COMMAND_MOVE)
  {
    if(move_command != 0)
    {
      printErrorMessage(COMMAND_NOT_ALLOWED);
      return false;
    }
    if(command_params.size() != 3)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    move_command++;
    Move move(COMMAND_MOVE, current_worm);
    move.execute(*this, command_params);
    return false;
  }
  else if(command_params.at(0) == COMMAND_CHOOSE)
  {
    if(command_params.size() != 2)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    Choose choose(COMMAND_MOVE, current_worm);
    return choose.execute(*this, command_params) == 0;
  }
  else if(command_params.at(0) == COMMAND_ACTION)
  {
    if(command_params.size() > 3)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    Action action(COMMAND_MOVE, current_worm);
    action.execute(*this, command_params);
    return true;
  }
  else
  {
    printErrorMessage(UNKNOWN_COMMAND);
    return false;
  }
}

