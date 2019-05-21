//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
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
#include "Quit.h"
#include "Action.h"
#include "Choose.h"
#include "Play.h"
#include "Whoami.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <vector>
#include <memory>

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
using std::shared_ptr;
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
const string Game::COMMAND_PLAY = "play";
const string Game::COMMAND_WHOAMI = "whoami";


const string Game::GUN = "gun";
const string Game::BAZOOKA = "bazooka";
const string Game::TELEPORT = "teleport";
const string Game::BLOWTORCH = "blowtorch";
const string Game::MELEE = "melee";
const string Game::AIRSTRIKE = "airstrike";

const string Game::SHOT_MISSED = "Shot missed...";
const string Game::TORCH = "Torch ";
const string Game::SHOT = "Shot ";
const string Game::TOOK = " took ";
const string Game::TOOK_ACTION = ") took ";
const string Game::HP_FALL_DAMAGE = "hp fall damage";
const string Game::HP_DAMAGE = "hp damage";
const string Game::ATTACK_HIT_WORM = "Attack hit Worm at position (";
const string Game::BRACKET_1 = " (";
const string Game::BRACKET_2 = ")";
const string Game::COMMA = ", ";

//------------------------------------------------------------------------------
Game::Game() : board_width_(0), board_height_(0), quit_(false), map_(),
               wormNumber(), chest_Number_(), ghost_mode_(false)
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
      cout << "[ERROR] invalid config file!" << endl;
      break;
    case INVALID_TARGET:
      cout << "[ERROR] invalid target!" << endl;
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
    case INVALID_PARAMETER:
      cout << "[ERROR] invalid parameter!" << endl;
      break;
    case COMMAND_NOT_ALLOWED:
      cout << "[ERROR] command currently not allowed!" << endl;
      break;
    case NO_AMMUNITION:
      cout << "[ERROR] no ammunition" << endl;
      break;
    case MEMORY_ERROR:
      break;
    case END_GAME:
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
      cout << wormNumber.at(current_worm).getName() << BRACKET_1 <<
           wormNumber.at(current_worm).getId() << BRACKET_2 << " drowned." <<
           endl;
      break;
    case FELL:
      cout << wormNumber.at(current_worm).getName() << BRACKET_1 <<
           wormNumber.at(current_worm).getId() << BRACKET_2 <<
           " fell into his death." << endl;
      break;
    case OUT_OF_MAP:
      cout << wormNumber.at(current_worm).getName() << BRACKET_1 <<
           wormNumber.at(current_worm).getId() << BRACKET_2 <<
           " fell out of the map." << endl;
      break;
    case DIED:
      cout << wormNumber.at(current_worm).getName() << BRACKET_1 <<
           wormNumber.at(current_worm).getId() << BRACKET_2 << " died." << endl;
      break;
  }
}

//------------------------------------------------------------------------------
int Game::loadConfig(const string &cfg_file)
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
       && row < ((board_height_ - 1) * board_width_)) // Saves each field
      // type to a position in the map
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::AIR)));
    }
    else if(keyword.at(index) == 'E' && row != 0)
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::EARTH)));
    }
    else if(keyword.at(index) == 'W' && row != 0
            && row >= ((board_height_ - 1) * board_width_))
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
    col = random->getRandomInt(0, board_width_ - 1);
    while(map_.at(currentField(row, col)).getType() == Field::WORM)
    {
      col = random->getRandomInt(0, board_width_ - 1);
    }
    while(map_.at(belowCurrentField(row, col)).getType() == Field::AIR)
    {
      row++; // row gets increased to handle gravity
    }
    wormNumber.at(index - 1).setPosition(row, col);
    cout << "spawning " << wormNumber.at(index - 1).getName() << BRACKET_1
         << wormNumber.at(index - 1).getId() << BRACKET_2 << " at " << "(0, "
         << col << BRACKET_2 << endl;
    if(map_.at(belowCurrentField(row, col)).getType() == Field::WATER)
    {
      printDeathCases(DROWNED, (index - 1));
      wormNumber.at(index - 1).setHp(0);
    }
    else
    {
      map_.at(currentField(row, col)).setType(Field::WORM);
      wormNumber.at(index - 1).setHp(100);
    }
    row = 0;
    wormNumber.at(index - 1).setWeapons();
    wormNumber.at(index - 1).setCurrentWeapon(0);
  }
}

//------------------------------------------------------------------------------
bool Game::createChest(Random *random)
{
  int col = random->getRandomInt(0, board_width_ - 1);
  int weapon_number = random->getRandomInt(0, NUMBER_OF_WEAPONS - 1);
  int row = 0;
  while(((map_.at(belowCurrentField(row, col)).getType() == Field::AIR ||
          map_.at(belowCurrentField(row, col)).getType() == Field::WORM)
         && map_.at(currentField(row, col)).getType() == Field::AIR))
  {
    row++; // row gets increased to handle gravity
  }
  if((map_.at(belowCurrentField(row, col)).getType() == Field::EARTH ||
      map_.at(belowCurrentField(row, col)).getType() == Field::CHEST)
     && map_.at(currentField(row, col)).getType() != Field::WORM)
  {
    try
    {
      shared_ptr<Chest> chest(new Chest(weapon_number, row, col));
      chest_Number_.emplace_back(chest);  // Vector to save Chest Positions
    }
    catch(std::bad_alloc &)
    {
      return true;
    }
    map_.at(currentField(row, col)).setType(Field::CHEST);
  }
  else if(map_.at(currentField(row, col)).getType() == Field::WORM)
  {
    wormNumber.at(findWorm(row, col)).getWeapons().at(
      weapon_number + 1).increaseAmmo();
    cout << wormNumber.at(findWorm(row, col)).getName() << BRACKET_1
         << wormNumber.at(findWorm(row, col)).getId()
         << ") picked up 1 of "
         << wormNumber.at(findWorm(row, col)).getWeapons().at(
           weapon_number + 1).getName() << endl;
  }
  return false;
}

//------------------------------------------------------------------------------
void Game::findChest(int row, int col, int current_worm)
{
  for(unsigned int index = 0; index < chest_Number_.size(); index++)
  {
    if(((chest_Number_.at(index)->getRow() * board_width_) +
        chest_Number_.at(index)->getCol())
       == (row * board_width_) + col)
    {
      map_.at(currentField(row, col)).setType(Field::WORM);
      wormNumber.at(current_worm).setPosition(row, col);
      wormNumber.at(current_worm).getWeapons().at(
        chest_Number_.at(index)->getIdChest() + 1).increaseAmmo();
      cout << wormNumber.at(current_worm).getName() << BRACKET_1
           << wormNumber.at(current_worm).getId()
           << ") picked up 1 of " <<
           wormNumber.at(current_worm).getWeapons().at(
             chest_Number_.at(index)->getIdChest() + 1).getName() << endl;
      shared_ptr<Chest> temp(chest_Number_.at(index));
      chest_Number_.erase(chest_Number_.begin() + index);
      break;
    }
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
            if(((index_col + (index_row - 1) * board_width_) ==
                (wormNumber.at(count).getCol() +
                 wormNumber.at(count).getRow() * board_width_))
               && wormNumber.at(count).getHp() > 0)
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
    if(checkWinner())
    {
      return EVERYTHING_OK;
    }
    if(setPlayerAndWorm(current_worm, player, turn_one, turn_two))
    {
      return 0; //wormNumber.at(current_worm) makes next move
    }
    wormNumber.at(current_worm).setCurrentWeapon(0); // sets gun to default
    move_command = 0;
    while(!userInput(current_worm, move_command))
    {
    }
    if(quit_)
    {
      break;
    }
    wormGravityCheck();
    chestGravity();
    if(createChest(&random))// adds chest on the end of every turn
    {
      return MEMORY_ERROR;
    }
    printMap();
    if(checkWinner())
    {
      return EVERYTHING_OK;
    }
  }
  return EVERYTHING_OK;
}

//------------------------------------------------------------------------------
int Game::checkWinner()
{
  int count_dead_worms = 0;
  for(int index = 0; index < 6; index++)
  {
    if(wormNumber.at(index).getHp() <= 0)
    {
      count_dead_worms++;
    }
  }
  if(count_dead_worms == 6)
  {
    cout << "END: Draw" << endl;
    return END_GAME;
  }
  else
  {
    count_dead_worms = 0;
  }
  for(int index = 0; index < 3; index++)
  {
    if(wormNumber.at(index).getHp() <= 0)
    {
      count_dead_worms++;
    }
  }
  if(count_dead_worms == 3)
  {
    cout << "END: Player 2 win!" << endl;
    return END_GAME;
  }
  else
  {
    count_dead_worms = 0;
  }
  for(int index = 3; index < 6; index++)
  {
    if(wormNumber.at(index).getHp() <= 0)
    {
      count_dead_worms++;
    }
  }
  if(count_dead_worms == 3)
  {
    cout << "END: Player 1 win!" << endl;
    return END_GAME;
  }
  return EVERYTHING_OK;
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

    if(wormNumber.at(current_worm).getHp() > 0)
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
           BRACKET_1 << wormNumber.at(current_worm).getId() << ") at " << "("
           << wormNumber.at(current_worm).getRow()
           << COMMA << wormNumber.at(current_worm).getCol() <<
           ") ready" << endl;
      return EVERYTHING_OK;
    }
  }
  return 1; // If one Player has no more accessible worms
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
  int step_direction = (col + 1);
  if(left_steps)
  {
    step_direction = (col - 1); // left direction
  }
  if(step_direction >= board_width_ || step_direction < 0
     || row >= board_height_)
  {
    wormNumber.at(current_worm).setHp(0);
    return false;
  }
  if(row > 0)
  {
    map_.at(currentField(row, col)).setType(Field::AIR);
  }
  if(map_.at(targetField(row, step_direction)).getType() ==
     Field::CHEST) // Step command
  {
    findChest(row, step_direction, current_worm);
    if(map_.at(currentField(row, col)).getType() == Field::WORM
       && map_.at(currentField(row, col)).getType() != Field::WORM)
    {
      map_.at(currentField(row, col)).setType(Field::AIR);
    }
    if(gravity(current_worm, row, step_direction))
    {
      col = step_direction;
      return true;
    }
  }
  if(map_.at(targetField(row, step_direction)).getType() ==
     Field::AIR) // Step command
  {
    if(map_.at(currentField(row, col)).getType() == Field::WORM
       && map_.at(currentField(row, col)).getType() != Field::WORM)
    {
      map_.at(currentField(row, col)).setType(Field::AIR);
    }
    if(gravity(current_worm, row, step_direction))
    {
      col = step_direction;
      return true;
    }
  }
  try
  {
    if((map_.at(aboveCurrentField(row, col)).getType() != Field::EARTH)
       &&
       ((map_.at(targetField(row, step_direction)).getType() == Field::WORM ||
         map_.at(targetField(row, step_direction)).getType() == Field::EARTH)
        &&
        map_.at(aboveTargetField(row, step_direction)).getType() ==
        Field::AIR)) // Climb command
    {
      map_.at(aboveTargetField(row, step_direction)).setType(Field::WORM);
      wormNumber.at(current_worm).setPosition((row - 1), step_direction);
      row--;
      col = step_direction;
      return true;
    }
    else if((map_.at(aboveCurrentField(row, col)).getType() != Field::EARTH)
            && ((map_.at(targetField(row, step_direction)).getType() ==
                 Field::WORM ||
                 map_.at(targetField(row, step_direction)).getType() ==
                 Field::EARTH)
                &&
                map_.at(aboveTargetField(row, step_direction)).getType() ==
                Field::CHEST)) // Climb command into Chest
    {
      row--;
      findChest(row, step_direction, current_worm);
      col = step_direction;
      return true;
    }
  }
  catch(std::out_of_range &)
  {
    map_.at(currentField(row, col)).setType(Field::WORM);
    return false;
  }
  map_.at(currentField(row, col)).setType(Field::WORM);
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
      else if(((col + 1) > board_width_) || (col - 1) < 0)
      {
        map_.at(currentField(row, col)).setType(Field::AIR);
        wormNumber.at(current_worm).setHp(0);
        printDeathCases(OUT_OF_MAP, current_worm);
        break;
      }
      break;
    }
    chestGravity();
    wormGravityCheck();
  }
}

//------------------------------------------------------------------------------
void Game::wormGravityCheck()
{
  int row_gravity;
  int check_row;
  int col_gravity = 0;
  int next_round_flag = 1;
  while(next_round_flag)
  {
    next_round_flag = 0;
    for(int index = 0; index < 6; index++)
    {
      row_gravity = wormNumber.at(index).getRow();
      check_row = wormNumber.at(index).getRow();
      col_gravity = wormNumber.at(index).getCol();
      gravity(index, row_gravity, col_gravity);
      if(row_gravity != check_row)
      {
        next_round_flag = 1;
      }
      wormNumber.at(index).setPosition(row_gravity, col_gravity);
    }
  }
}

//------------------------------------------------------------------------------
void Game::chestGravity()
{
  for(unsigned int index = 0; index < chest_Number_.size(); index++)
  {
    int row = chest_Number_.at(index)->getRow();
    int col = chest_Number_.at(index)->getCol();
    while(map_.at(belowCurrentField(row, col)).getType() == (Field::AIR))
    {
      map_.at(currentField(row, col)).setType(Field::AIR);
      row++;
    }
    if(map_.at(belowCurrentField(row, col)).getType() == Field::EARTH
       || map_.at(belowCurrentField(row, col)).getType() == Field::CHEST)
    {
      map_.at(currentField(row, col)).setType(Field::CHEST);
      chest_Number_.at(index)->setPosition(row, col);
    }
    if(map_.at(belowCurrentField(row, col)).getType() == Field::WORM)
    {
      wormNumber.at(findWorm(row + 1, col)).getWeapons().at(
        chest_Number_.at(index)->getIdChest() + 1).increaseAmmo();
      map_.at(currentField(row, col)).setType(Field::AIR);
      cout << wormNumber.at(findWorm(row + 1, col)).getName() << BRACKET_1
           << wormNumber.at(findWorm(row + 1, col)).getId()
           << ") picked up 1 of " <<
           wormNumber.at(findWorm(row + 1, col)).getWeapons().at(
             chest_Number_.at(index)->getIdChest() + 1).getName()
           << endl;
      shared_ptr<Chest> temp(chest_Number_.at(index));
      chest_Number_.erase(chest_Number_.begin() + index);
    }
  }
}

//------------------------------------------------------------------------------
vector<Worm> Game::getWormNumber()
{
  return wormNumber;
}

//------------------------------------------------------------------------------
int Game::getBoardWidth()
{
  return board_width_;
}

//------------------------------------------------------------------------------
int Game::getBoardHeight()
{
  return board_height_;
}

//------------------------------------------------------------------------------
bool Game::userInput(int current_worm, int &move_command)
{
  string input_line;
  string param;
  vector<string> command_params;

  cout << COMMAND_PROMPT;
  getline(cin, input_line);
  std::transform(input_line.begin(), input_line.end(), input_line.begin(),
                 ::tolower); // case insensitiv
  if(cin.eof())
  {
    Quit quit(COMMAND_QUIT);
    return quit.execute(*this, command_params) == 0;
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
  return !checkOneParameterCommand(command_params, current_worm, move_command);
}

//------------------------------------------------------------------------------
bool Game::checkOneParameterCommand(std::vector<std::string> command_params,
                                    int current_worm, int &move_command)
{
  if(command_params.size() == 1 && (command_params.at(0) != COMMAND_MOVE &&
                                    command_params.at(0) != COMMAND_CHOOSE &&
                                    command_params.at(0) != COMMAND_ACTION))
  {
    if(command_params.at(0) == COMMAND_QUIT)
    {
      Quit quit(COMMAND_QUIT);
      return quit.execute(*this, command_params);
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
    else if(command_params.at(0) == COMMAND_PLAY)
    {
      Play play(COMMAND_PLAY, current_worm);
      return play.execute(*this, command_params) ==
             0; //return wert muss auf true geandert werden, wenn befehl
                // ausgefuehrt
    }
    else if(command_params.at(0) == COMMAND_WHOAMI)
    {
      Whoami whoami(COMMAND_WHOAMI);
      return whoami.execute(*this, command_params) == 0;
    }
    else
    {
      printErrorMessage(UNKNOWN_COMMAND);
      return true;
    }
  }
  else if(command_params.size() != 1 && (command_params.at(0) == COMMAND_QUIT
                                         ||
                                         command_params.at(0) == COMMAND_HELP
                                         ||
                                         command_params.at(0) == COMMAND_STATE
                                         ||
                                         command_params.at(0) == COMMAND_MAP))
  {
    printErrorMessage(WRONG_PARAMETER_COUNT);
    return true;
  }
  else
  {
    return !checkMoreParameterCommand(command_params, current_worm,
                                      move_command);
  }
}

//------------------------------------------------------------------------------
bool Game::checkMoreParameterCommand(std::vector<std::string> command_params,
                                     int current_worm, int &move_command)
{
  if(command_params.at(0) == COMMAND_MOVE)
  {
    if(command_params.size() != 3)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    if(move_command != 0)
    {
      printErrorMessage(COMMAND_NOT_ALLOWED);
      return false;
    }
    move_command++;
    Move move(COMMAND_MOVE, current_worm);
    if(move.execute(*this, command_params))
    {
      move_command = 0;
      printErrorMessage(INVALID_PARAMETER);
    }
    // If worm is dead, next Worm starts making commands
    return wormNumber.at(current_worm).getHp() <= 0;
  }
  else if(command_params.at(0) == COMMAND_CHOOSE)
  {
    if(command_params.size() != 2)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    Choose choose(COMMAND_MOVE, current_worm);
    if(choose.execute(*this, command_params))
    {
      printErrorMessage(INVALID_PARAMETER);
    }
    return false;
  }
  else if(command_params.at(0) == COMMAND_ACTION)
  {
    if(command_params.size() > 3)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    Action action(COMMAND_MOVE, current_worm);
    if(action.execute(*this, command_params))
    {
      if(command_params.size() == 3
         && wormNumber.at(current_worm).getCurrentWeapon() == 2)
      {
        printErrorMessage(INVALID_TARGET);
      }
      else if(command_params.size() == 3)
      {
        printErrorMessage(INVALID_PARAMETER);
      }
      else
      {
        printErrorMessage(WRONG_PARAMETER_COUNT);
      }
      return false;
    }
    return true; // Next turn
  }
  else
  {
    printErrorMessage(UNKNOWN_COMMAND);
    return false;
  }
}

//------------------------------------------------------------------------------
bool Game::gravity(int current_worm, int &row, int col)
{
  int count = 0;
  try
  {
    if(map_.at(belowCurrentField(row, col)).getType() == Field::AIR)
    {
      map_.at(currentField(row, col)).setType(Field::AIR);
      while(map_.at(belowCurrentField(row, col)).getType() ==
            Field::AIR) //((row + 1) * board_width_ + col)
      {
        row++;
        count++;
      }
      if(count > 1 &&
         (map_.at(belowCurrentField(row, col)).getType() != Field::WATER
          &&
          map_.at(belowCurrentField(row, col)).getType() != Field::CHEST))
      {
        wormNumber.at(current_worm).damage((count - 1) * 10);
        if(wormNumber.at(current_worm).getHp() <= 0)
        {
          printDeathCases(FELL, current_worm);
        }
        else
        {
          cout << wormNumber.at(current_worm).getName() << BRACKET_1
               << wormNumber.at(current_worm).getId() << BRACKET_2
               << TOOK << (count - 1) * 10 << HP_FALL_DAMAGE << endl;
        }
      }
    }
    if((map_.at(belowCurrentField(row, col)).getType() == Field::EARTH
        || map_.at(belowCurrentField(row, col)).getType() == Field::WORM)
       && wormNumber.at(current_worm).getHp() > 0)
    {
      map_.at(currentField(row, col)).setType(Field::WORM);
      wormNumber.at(current_worm).setPosition(row, col);
    }
    else if(map_.at(belowCurrentField(row, col)).getType() == Field::CHEST)
    {
      while(map_.at(belowCurrentField(row, col)).getType() == Field::CHEST)
      {
        row++;
        count++;
        findChest(row, col, current_worm);
      }
      if(count > 1)
      {
        wormNumber.at(current_worm).damage((count - 1) * 10);
        if(wormNumber.at(current_worm).getHp() <= 0)
        {
          map_.at(currentField(row, col)).setType(Field::AIR);
          printDeathCases(FELL, current_worm);
        }
        else
        {
          cout << wormNumber.at(current_worm).getName() << BRACKET_1
               << wormNumber.at(current_worm).getId() << BRACKET_2
               << TOOK << (count - 1) * 10 << HP_FALL_DAMAGE << endl;
        }
      }

    }
    else if(map_.at(belowCurrentField(row, col)).getType() == Field::WATER &&
            wormNumber.at(current_worm).getHp() > 0)
    {
      wormNumber.at(current_worm).setHp(0);
      map_.at(currentField(row, col)).setType(Field::AIR);
      printDeathCases(DROWNED, current_worm);
      return false;
    }
    return true;
  }
  catch(std::out_of_range &)
  {
    if(wormNumber.at(current_worm).getHp() > 0)
    {
      printDeathCases(OUT_OF_MAP, current_worm);
    }
    wormNumber.at(current_worm).setHp(0);
    return false;
  }
}

//------------------------------------------------------------------------------
int Game::chooseWeapon(int current_worm, std::vector<std::string> &params)
{
  if(params.at(1) == GUN)
  {
    wormNumber.at(current_worm).setCurrentWeapon(0);
    std::cout << "Chose weapon gun Ammunition: inf" << std::endl;
  }
  else if(params.at(1) == BAZOOKA &&
          wormNumber.at(current_worm).getWeapons().at(0).getAmmo())
  {
    if(wormNumber.at(current_worm).getWeapons().at(1).getAmmo() > 0)
    {
      wormNumber.at(current_worm).setCurrentWeapon(1);
      std::cout << "Chose weapon bazooka Ammunition: " <<
                wormNumber.at(current_worm).getWeapons().at(1).getAmmo()
                << std::endl;
    }
    else
    {
      printErrorMessage(NO_AMMUNITION);
    }
  }
  else if(params.at(1) == TELEPORT)
  {
    if(wormNumber.at(current_worm).getWeapons().at(2).getAmmo() > 0)
    {
      wormNumber.at(current_worm).setCurrentWeapon(2);
      std::cout << "Chose weapon teleport Ammunition: " <<
                wormNumber.at(current_worm).getWeapons().at(2).getAmmo()
                << std::endl;
    }
    else
    {
      printErrorMessage(NO_AMMUNITION);
    }
  }
  else if(params.at(1) == BLOWTORCH)
  {
    if(wormNumber.at(current_worm).getWeapons().at(3).getAmmo() > 0)
    {
      wormNumber.at(current_worm).setCurrentWeapon(3);
      std::cout << "Chose weapon blowtorch Ammunition: " <<
                wormNumber.at(current_worm).getWeapons().at(3).getAmmo()
                << std::endl;
    }
    else
    {
      printErrorMessage(NO_AMMUNITION);
    }
  }
  else if(params.at(1) == MELEE)
  {
    if(wormNumber.at(current_worm).getWeapons().at(4).getAmmo() > 0)
    {
      wormNumber.at(current_worm).setCurrentWeapon(4);
      std::cout << "Chose weapon melee Ammunition: " <<
                wormNumber.at(current_worm).getWeapons().at(4).getAmmo()
                << std::endl;
    }
    else
    {
      printErrorMessage(NO_AMMUNITION);
    }
  }
  else if(params.at(1) == AIRSTRIKE)
  {
    if(wormNumber.at(current_worm).getWeapons().at(5).getAmmo() > 0)
    {
      wormNumber.at(current_worm).setCurrentWeapon(5);
      std::cout << "Chose weapon airstrike Ammunition: " <<
                wormNumber.at(current_worm).getWeapons().at(5).getAmmo()
                << std::endl;
    }
    else
    {
      printErrorMessage(NO_AMMUNITION);
    }
  }
  else
  {
    return INVALID_PARAMETER;
  }
  return EVERYTHING_OK;
}

//------------------------------------------------------------------------------
int Game::findWorm(int row, int col)
{
  for(int index = 0; index < 6; index++)
  {
    if(((wormNumber.at(index).getRow() * board_width_) +
        wormNumber.at(index).getCol())
       == (row * board_width_) + col)
    {
      return index;
    }
  }
  return INVALID_TARGET;
}

//------------------------------------------------------------------------------
void Game::actionCommand(int current_worm, int current_weapon, int damage)
{ // Melee
  if(wormNumber.at(current_worm).getWeapons().at(current_weapon).getAmmo()
     <= 0)
  {
    printErrorMessage(NO_AMMUNITION);
    return;
  }
  int row = wormNumber.at(current_worm).getRow();
  int col = wormNumber.at(current_worm).getCol();
  wormNumber.at(current_worm).getWeapons().at(current_weapon).decreaseAmmo();
  try
  {
    for(int index = -1; index < 2; index++)
    {
      if(map_.at(aboveCurrentField(row, col) +
                 index).getType() == Field::WORM
         && wormNumber.at(findWorm((row - 1), (col + index))).getHp() > 0)
      {
        wormNumber.at(findWorm((row - 1), (col + index))).damage(damage);
        cout << ATTACK_HIT_WORM << (row - 1) << COMMA
             << (col + index) << BRACKET_2 << endl;
        if(wormNumber.at(findWorm(row - 1, col + index)).getHp() <= 0)
        {
          map_.at(aboveCurrentField(row, col + index)).setType(Field::AIR);
          printDeathCases(DIED, findWorm((row - 1), col + index));
        }
        else
        {
          cout << wormNumber.at(findWorm(row - 1, col + index)).getName()
               << BRACKET_1 << wormNumber.at(findWorm(row - 1, col
                                                               + index)).getId()
               << TOOK_ACTION << damage << HP_DAMAGE << endl;
        }
      }
    }
  }
  catch(std::out_of_range &)
  {
  }
  try
  {
    if(map_.at(currentField(row, col) + 1).getType() == Field::WORM
       && wormNumber.at(findWorm(row, col + 1)).getHp() > 0)
    {
      wormNumber.at(findWorm(row, (col + 1))).damage(damage);
      cout << ATTACK_HIT_WORM << row << COMMA << (col + 1) << BRACKET_2
           << endl;
      if(wormNumber.at(findWorm(row, col + 1)).getHp() <= 0)
      {
        map_.at(currentField(row, col + 1)).setType(Field::AIR);
        printDeathCases(DIED, findWorm((row), col + 1));
      }
      else
      {
        cout << wormNumber.at(findWorm(row, col + 1)).getName() << BRACKET_1
             << wormNumber.at(findWorm(row, col + 1)).getId() << TOOK_ACTION <<
             damage << HP_DAMAGE << endl;
      }
    }
  }
  catch(std::out_of_range &)
  {
  }
  try
  {
    for(int index = 1; index > -2; index--)
    {
      if(map_.at(belowCurrentField(row, col) + index).getType() == Field::WORM
         && wormNumber.at(findWorm((row + 1), (col + index))).getHp() > 0)
      {
        wormNumber.at(findWorm((row + 1), (col + index))).damage(damage);
        cout << ATTACK_HIT_WORM << (row + 1) << COMMA
             << (col + index) << BRACKET_2 << endl;
        if(wormNumber.at(findWorm(row + 1, col + index)).getHp() <= 0)
        {
          map_.at(belowCurrentField(row, col + index)).setType(Field::AIR);
          printDeathCases(DIED, findWorm((row + 1), col + index));
        }
        else
        {
          cout << wormNumber.at(findWorm(row + 1, col + index)).getName()
               << BRACKET_1 << wormNumber.at(findWorm(row + 1, col +
                                                               index)).getId()
               << TOOK_ACTION << damage << HP_DAMAGE << endl;
        }
      }
    }
  }
  catch(std::out_of_range &)
  {
  }
  try
  {
    if(map_.at(currentField(row, col) - 1).getType() == Field::WORM
       && wormNumber.at(findWorm(row, col - 1)).getHp() > 0)
    {
      wormNumber.at(findWorm(row, (col - 1))).damage(damage);
      cout << ATTACK_HIT_WORM << row << COMMA << (col - 1)
           << BRACKET_2 << endl;
      if(wormNumber.at(findWorm(row, col - 1)).getHp() <= 0)
      {
        map_.at(currentField(row, col - 1)).setType(Field::AIR);
        printDeathCases(DIED, findWorm((row), col - 1));
      }
      else
      {
        cout << wormNumber.at(findWorm(row, col - 1)).getName() << BRACKET_1
             << wormNumber.at(findWorm(row, col - 1)).getId() << TOOK_ACTION <<
             damage << HP_DAMAGE << endl;
      }
    }
  }
  catch(std::out_of_range &)
  {
  }
}

//------------------------------------------------------------------------------
void Game::makeDamage(int row, int col, int damage)
{
  try
  {
    if(map_.at(currentField(row, col)).getType() == Field::CHEST)
    {
      for(unsigned int index = 0; index < chest_Number_.size(); index++)
      {
        if((chest_Number_.at(index)->getRow() * board_width_ +
            chest_Number_.at(index)->getCol())
           == (row * board_width_ + col))
        {
          map_.at(currentField(row, col)).setType(Field::AIR);
          shared_ptr<Chest> temp(chest_Number_.at(index));
          chest_Number_.erase(chest_Number_.begin() + index);
          if(damage == BLOWTORCH_DAMAGE) // blowtorch
          {
            cout << TORCH;
          }
          else
          {
            cout << SHOT;
          }
          cout << "hit Chest at position (" << row << COMMA << col << BRACKET_2
               << endl;
          break;
        }
      }
    }
    else if(map_.at(currentField(row, col)).getType() == Field::EARTH)
    {
      map_.at(currentField(row, col)).setType(Field::AIR);
      if(damage == BLOWTORCH_DAMAGE) // blowtorch
      {
        cout << TORCH;
      }
      else
      {
        cout << SHOT;
      }
      cout << "hit Earth at position (" << row << COMMA << col << BRACKET_2
           << endl;
    }
    else if(map_.at(currentField(row, col)).getType() == Field::WORM &&
            wormNumber.at(findWorm(row, col)).getHp() > 0)
    {
      wormNumber.at(findWorm(row, col)).damage(damage);
      if(damage == BLOWTORCH_DAMAGE) // blowtorch
      {
        cout << TORCH;
      }
      else
      {
        cout << SHOT;
      }
      cout << "hit Worm at position (" << row << COMMA << col << BRACKET_2
           << endl;
      if(wormNumber.at(findWorm(row, col)).getHp() <= 0)
      {
        map_.at(currentField(row, col)).setType(Field::AIR);
        printDeathCases(DIED, findWorm((row), col));
      }
      else
      {
        cout << wormNumber.at(findWorm(row, col)).getName() << BRACKET_1
             << wormNumber.at(findWorm(row, col)).getId() << TOOK_ACTION <<
             damage << HP_DAMAGE << endl;
        wormGravityCheck();
      }
    }
  }
  catch(std::out_of_range &)
  {
    if(damage != BLOWTORCH_DAMAGE) // Blowtorch
    {
      cout << SHOT_MISSED << endl;
    }
  }
}

//------------------------------------------------------------------------------
bool Game::findTarget(int &row, int &col, int direction)
{
  try
  {
    switch(direction)
    {
      case 0:
        while(map_.at(currentField(row, (col + CHECK_LEFT))).getType() ==
              Field::AIR) // left
        {
          col--;
        }
        col--;
        break;
      case 1:
        while(map_.at(currentField(row, col) + CHECK_RIGHT).getType() ==
              Field::AIR) // right
        {
          col++;
        }
        col++;
        break;
      case 2:
        while(map_.at(belowCurrentField(row, col)).getType() ==
              Field::AIR) // down
        {
          row++;
        }
        row++;
        break;
      case 3:
        while(map_.at(aboveCurrentField(row, col)).getType() ==
              Field::AIR) // up
        {
          row--;
        }
        row--;
        break;
      case 4:
        while(map_.at(currentField(row, col) +
                      (board_width_ + CHECK_LEFT_DOWN)).getType() ==
              Field::AIR) // left-down
        {
          row++;
          col--;
        }
        row++;
        col--;
        break;
      case 5:
        while(map_.at(currentField(row, col) +
                      (board_width_ + CHECK_RIGHT_DOWN)).getType() ==
              Field::AIR) // right-down
        {
          row++;
          col++;
        }
        row++;
        col++;
        break;
      case 6:
        while(map_.at(
          currentField(row, col) - (board_width_ + CHECK_LEFT_UP)).getType() ==
              Field::AIR) // left-up
        {
          row--;
          col--;
        }
        row--;
        col--;
        break;
      case 7:
        while(map_.at(
          currentField(row, col) - (board_width_ + CHECK_RIGHT_UP)).getType() ==
              Field::AIR) // right-up
        {
          row--;
          col++;
        }
        row--;
        col++;
        break;
      default:
        break;
    }
    if(row < 0 || col < 0 || row > board_height_ || col > board_width_)
    {
      throw std::out_of_range(SHOT_MISSED);
    }
  }
  catch(std::out_of_range &)
  {
    cout << SHOT_MISSED << endl;
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
void Game::actionDirectionCommand(int current_worm, int current_weapon,
                                  int damage, int direction)
{
  if(wormNumber.at(current_worm).getWeapons().at(current_weapon).getAmmo() <= 0)
  {
    printErrorMessage(NO_AMMUNITION);
    return;
  }
  if(current_weapon == BLOWTORCH_INT)
  {
    blowtorchCommand(current_worm, damage, direction, current_weapon);
    return;
  }
  int row = wormNumber.at(current_worm).getRow();
  int col = wormNumber.at(current_worm).getCol();

  if(findTarget(row, col, direction))
  {
    if(current_weapon == GUN_INT) // Gun
    {
      makeDamage(row, col, damage);
    }
    else if(current_weapon == BAZOOKA_INT) // Bazooka
    {
      wormNumber.at(current_worm).getWeapons()
        .at(current_weapon).decreaseAmmo();
      makeDamage(row, col, damage);
      makeDamage(row - CHECK_ROW, col, damage);
      makeDamage(row, col + CHECK_RIGHT, damage);
      makeDamage(row + CHECK_ROW, col, damage);
      makeDamage(row, col + CHECK_LEFT, damage);
    }
  }
}

//------------------------------------------------------------------------------
void Game::blowtorchCommand(int current_worm, int damage, int direction,
                            int current_weapon)
{
  wormNumber.at(current_worm).getWeapons().at(current_weapon).decreaseAmmo();
  int row = wormNumber.at(current_worm).getRow();
  int col = wormNumber.at(current_worm).getCol();
  for(int range = 1; range <= 5; range++)
  {
    switch(direction)
    {
      case 0: // l
        col--;
        break;
      case 1: // r
        col++;
        break;
      case 2: // d
        row++;
        break;
      case 3: // u
        row--;
        break;
      case 4: // ld
        row++;
        col--;
        break;
      case 5: // rd
        row++;
        col++;
        break;
      case 6: // lu
        row--;
        col--;
        break;
      case 7: // ru
        row--;
        col++;
        break;
      default:
        break;
    }
    makeDamage(row, col, damage);
  }
}

//------------------------------------------------------------------------------
void Game::actionColCommand(int current_worm, int current_weapon, int damage,
                            int col)
{
  if(wormNumber.at(current_worm).getWeapons().at(current_weapon).getAmmo() <= 0)
  {
    printErrorMessage(NO_AMMUNITION);
    return;
  }
  int row = 0;
  try
  {
    wormNumber.at(current_worm).getWeapons().at(current_weapon).decreaseAmmo();
    while(map_.at(currentField(row, col)).getType() == Field::AIR)
    {
      row++;
    }
    makeDamage(row, col, damage);
  }
  catch(std::out_of_range &)
  {
    cout << SHOT_MISSED << endl;
  }
}

//------------------------------------------------------------------------------
bool Game::actionRowColCommand(int current_worm, int current_weapon, int row,
                               int col)
{
  if(map_.at(currentField(row, col)).getType() == Field::AIR)
  {
    wormNumber.at(current_worm).getWeapons().at(current_weapon).decreaseAmmo();
    map_.at((wormNumber.at(current_worm).getRow() * board_width_)
            + wormNumber.at(current_worm).getCol()).setType(Field::AIR);
    gravity(current_worm, row, col);
    return true;
  }
  else if(map_.at(currentField(row, col)).getType() == Field::CHEST)
  {
    wormNumber.at(current_worm).getWeapons().at(current_weapon).decreaseAmmo();
    map_.at((wormNumber.at(current_worm).getRow() * board_width_)
            + wormNumber.at(current_worm).getCol()).setType(Field::AIR);
    findChest(row, col, current_worm);
    gravity(current_worm, row, col);
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void Sep::Game::setQuit(bool quit)
{
  quit_ = quit;
}

//------------------------------------------------------------------------------
int Sep::Game::currentField(int row, int col)
{
  return ((row * board_width_) + col);
}

//------------------------------------------------------------------------------
int Sep::Game::belowCurrentField(int row, int col)
{
  return ((row + 1) * board_width_ + col);
}

//------------------------------------------------------------------------------
int Sep::Game::aboveCurrentField(int row, int col)
{
  return (((row - 1) * board_width_) + col);
}

//------------------------------------------------------------------------------
int Sep::Game::targetField(int row, int step_direction)
{
  return ((row * board_width_) + step_direction);
}

//------------------------------------------------------------------------------
int Sep::Game::aboveTargetField(int row, int step_direction)
{
  return (((row - 1) * board_width_) + step_direction);
}

//------------------------------------------------------------------------------
void Game::setGhostMode()
{
  ghost_mode_ = true;
}

//------------------------------------------------------------------------------
int Game::playCommand(int current_worm, bool team)
{
  //if(wormNumber.at(current_worm).getWeapons().at(MELEE_INT).getAmmo() > 0)
  //{
  //  botInput(current_worm, "choose melee");
  //  botInput(current_worm, "action");
  //}
  //else
  //{
  //  botInput(current_worm, "action l");
  //}

  if(makeGhostActionCommand(current_worm, team))
  {
   // makeGhostMoveCommand(current_worm, team);
  }
  return true;
}

//------------------------------------------------------------------------------
bool Game::makeGhostActionCommand(int current_worm, bool team)
{
  string command;
  if(wormNumber.at(current_worm).getWeapons().at(MELEE_INT).getAmmo() > 0
      && testGhostMelee(current_worm, team))
  {
    botInput(current_worm, "choose melee");
    botInput(current_worm, "action");
    return true;
  }
  else
  {
    if(wormNumber.at(current_worm).getWeapons().at(BAZOOKA_INT).getAmmo() > 0)
    {
      botInput(current_worm, "choose bazooka");
      command = "command: choose bazooka";
    }
    else if(wormNumber.at(current_worm).getWeapons().at(BLOWTORCH_INT).getAmmo()
    > 0)
    {
      botInput(current_worm, "choose blowtorch");
      command = "command: choose blowtorch";
    }
    botInput(current_worm, "action l");
    cout << command << endl;
    cout << "command: action l" << endl;
    return true;
  }

}

//------------------------------------------------------------------------------
bool Game::testGhostMelee(int current_worm, bool team)
{
  int row = wormNumber.at(current_worm).getRow();
  int col = wormNumber.at(current_worm).getCol();
  try
  {
    for(int index = -1; index < 2; index++)
    {
      if(map_.at(aboveCurrentField(row, col) +
                 index).getType() == Field::WORM
         && wormNumber.at(findWorm((row - 1), (col + index))).getHp() > 0
         && ((team && findWorm((row - 1), (col + index)) > 2)
             || (!team && findWorm((row - 1), (col + index)) < 3)))
      {
        return true;
      }
    }
    if(map_.at(currentField(row, col) + 1).getType() == Field::WORM
       && wormNumber.at(findWorm(row, col + 1)).getHp() > 0
       && ((team && findWorm((row), (col + 1)) > 2)
           || (!team && findWorm((row), (col + 1)) < 3)))
    {
      return true;
    }
    for(int index = -1; index < 2; index++)
    {
      if(map_.at(belowCurrentField(row, col) +
                 index).getType() == Field::WORM
         && wormNumber.at(findWorm((row + 1), (col + index))).getHp() > 0
         && ((team && findWorm((row + 1), (col + index)) > 2)
             || (!team && findWorm((row + 1), (col + index)) < 3)))
      {
        return true;
      }
    }
    if(map_.at(currentField(row, col) - 1).getType() == Field::WORM
       && wormNumber.at(findWorm(row, col - 1)).getHp() > 0
       && ((team && findWorm((row), (col - 1)) > 2)
           || (!team && findWorm((row), (col - 1)) < 3)))
    {
      return true;
    }
    return false;
  }
  catch(std::out_of_range &)
  {
  }
}

//------------------------------------------------------------------------------
//void Game::makeGhostMoveCommand(int current_worm, bool team)
//{

//}

//------------------------------------------------------------------------------
bool Game::botInput(int current_worm, string command)
{
  string param;
  vector<string> command_params;
  int move_command = 0;

  stringstream input_stream(command);
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
  return !checkOneParameterCommand(command_params, current_worm, move_command);
}