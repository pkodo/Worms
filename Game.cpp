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
#include <iostream>
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

const string Game::MAGIC_VALUE = "#SWORMS";
const string Game::CHECK_FOR_SIZE = "SIZE:";
const string Game::CHECK_FOR_MAP = "MAP:";

const string Game::COMMAND_PROMPT = "sep> ";
const string Game::COMMAND_MOVE = "move";
const string Game::COMMAND_QUIT = "quit";



//------------------------------------------------------------------------------
Game::Game() : board_width_(0), board_height_(0), map_(), wormNumber()
{
  Game::map_.insert(pair<int, Field>(board_height_* board_width_,
      Field(Field::AIR)));
}

//------------------------------------------------------------------------------
Game::ErrorType Game::printErrorMessage(ErrorType type)
{
  switch (type)
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
    case EVERYTHING_OK:
      break;
    case UNKNOWN_COMMAND:
      cout << "[ERROR] unknown command!" << endl;
      break;
    case WRONG_PARAMETER_COUNT:
      cout << "[ERROR] wrong parameter count!" << endl;
      break;
  }
  return type;
}

//------------------------------------------------------------------------------
int Game::loadConfig(string cfg_file)
{
  int row = 0;
  ConfigKeywords check = SIZE;
  stringstream size, map;
  string file_input, keyword;

  ifstream file(cfg_file);
  if (!file.is_open())
  {
    return printErrorMessage(INVALID_CONFIGFILE);
  }

  if (!(file >> file_input) || file_input != MAGIC_VALUE) //Checks #SWORMS
  {
    return printErrorMessage(INVALID_CONFIGFILE);
  }

  while (getline(file, file_input))
  {
    if ((!file_input.empty()) && (file_input.at(0) != '#'))
    {
      if (check == SIZE) //Checks for SIZE:
      {
        size << file_input;
        size >> keyword >> board_width_ >> board_height_;
        check = MAP;
        if ((CHECK_FOR_SIZE != keyword || (board_width_ < MIN_LENGTH
            || board_width_ > MAX_LENGTH) || (board_height_ < MIN_LENGTH
            || board_height_ > MAX_LENGTH))) //Returns printError if the size of the
            // board  is too small or too big or the keyword SIZE was not found
        {
          return printErrorMessage(INVALID_CONFIGFILE);
        }
      }
      else if (check == MAP)
      {
        map << file_input;
        map >> keyword;
        check = MAPFIELDS;
        if ((CHECK_FOR_MAP != keyword))
        {
          return printErrorMessage(INVALID_CONFIGFILE);
        }
      }
      else if (check == MAPFIELDS)
      {
        int length = static_cast<int>(file_input.length());
        if (length != board_width_ || !createMapFields(file_input,row))
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
  for (int index = 0; index < board_width_; index++)
  {
    if (keyword.at(index) == 'A'
        && row < ((board_height_ - ONE) * board_width_)) // Saves each field
        // type to a position in the map
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::AIR)));
    }
    else if (keyword.at(index) == 'E' && row != 0)
    {
      map_.insert(pair<int, Field>(index + row, Field(Field::EARTH)));
    }
    else if (keyword.at(index) == 'W' && row != 0
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
    while ((map_.at(BELOW_CURRENT_FIELD).getType() == Field::AIR
    && map_.at(CURRENT_FIELD).getType() == Field::AIR))
    {
      row++; // row gets increased to handle gravity
    }
    wormNumber.at(index - 1).setPosition(row, col);
    cout << "spawning " << wormNumber.at(index - 1).getName() << " (" << wormNumber.at(index - 1).getId() << ")" << " at " << "(0," << col << ")" << endl;

    if(map_.at(BELOW_CURRENT_FIELD).getType() == Field::WATER)
    {
      cout << wormNumber.at(index - 1).getName() << " (" << wormNumber.at(index - 1).getId() << ")" << " drowned." << endl;
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



void Game::createChest(Random *random)
{
    int weapon_number = random->getRandomInt(0,4); // needs to be implemented
    int col = random->getRandomInt(0, board_width_ - 1);
    int row = 0;
    while ((map_.at(BELOW_CURRENT_FIELD).getType() == Field::AIR
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
  for (int index_row = 0; index_row <= (board_height_ + ONE); index_row++)
  {
    if (index_row == 0 || index_row == (board_height_ + ONE))
    {
      cout << "  ";
    }
    else
    {
      cout << setw(MAX_DIGITS) << (index_row - ONE);
    }
    for (int index_col = 0; index_col < board_width_; index_col++)
    {
      if (index_row == 0 || index_row == (board_height_ + ONE))
      {
        if (count_to_ten == MIN_LENGTH)
        {
          count_to_ten = 0;
        }
        cout << count_to_ten;
        count_to_ten++;
      }
      else
      {
          if(map_.at(index_col + (index_row - ONE) * board_width_).getType() != Field::WORM)
          {
             cout << map_.at(index_col + (index_row - ONE) * board_width_).getCharacter();
          }
          else
          {
            for(int count = 0; count < 6; count++)
            {
              if((index_col + (index_row - ONE) * board_width_) ==
              (wormNumber.at(count).getCol() + wormNumber.at(count).getRow() * board_width_))
              {
                cout << wormNumber.at(count).getCharacter();
              }
            }
          }
      count_to_ten = 0;
      }
    }
    if (index_row == 0 || index_row == (board_height_ + ONE))
    {
      cout << endl;
    }
    else
    {
      cout << setw(MAX_DIGITS) << (index_row - ONE) << endl;
    }
  }
}



int Game::gameLoop()
{
    int current_worm = 0;
    int player = 1;

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
        while(!userInput());
        move(wormNumber.at(current_worm).getRow(), wormNumber.at
        (current_worm).getCol(), next_move_);
        createChest(&random); // adds chest on the end of every turn
        //cin.get();
        printMap();
    }
}




int Game::setPlayerAndWorm(int &current_worm, int &player, int& turn_one, int& turn_two)
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
                 " (" << wormNumber.at(current_worm).getId() << ") at " << "(" << wormNumber.at(current_worm).getRow()
                 << ", " << wormNumber.at(current_worm).getCol() << ") ready" << endl;
            return EVERYTHING_OK;
        }
    }
    return 1; // If one Player has no more accessible worms
}


//------------------------------------------------------------------------------
void Game::testWormTower(int &row, int &col, int &detect_worm_tower)
{
  if (map_.at(ABOVE_CURRENT_FIELD).getType() == Field::WORM)
  {
    while (map_.at(ABOVE_CURRENT_FIELD).getType() == Field::WORM)
    {
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
  if (steps < 0)
  {
    left_steps = true;
  }
  if ((steps = std::abs(steps)) > MAX_STEPS)
  {
    steps = MAX_STEPS;
  }
  return left_steps;
}

//------------------------------------------------------------------------------
bool Game::makeMove(int &row, int &col, bool left_steps)
{
  int detect_worm_tower = row;
  int step_direction = (col + ONE);
  if (left_steps)
  {
    step_direction = (col - ONE); // left direction
  }
  if (step_direction >= board_width_ || step_direction < 0)
  {
      return false;
  }
  if ((map_.at(ABOVE_CURRENT_FIELD).getType() != Field::EARTH)
      && ((map_.at(TARGET_FIELD).getType() == Field::WORM ||
      map_.at(TARGET_FIELD).getType() == Field::EARTH)
      && map_.at(ABOVE_TARGET_FIELD).getType() == Field::AIR)) // Climb command
  {
    testWormTower(row, col, detect_worm_tower);
    map_.at(ABOVE_TARGET_FIELD).setType(Field::WORM);
    row--;
    col = step_direction;
    return true;
  }
  if (map_.at(TARGET_FIELD).getType() == Field::AIR) // Step command
  {
    testWormTower(row, col, detect_worm_tower);
    while ((map_.at(BELOW_TARGET_FIELD).getType() == Field::AIR))
    {
      row++;
    }
    if (map_.at(BELOW_TARGET_FIELD).getType() == Field::EARTH
        || map_.at(BELOW_TARGET_FIELD).getType() == Field::WORM)
    {
      map_.at(TARGET_FIELD).setType(Field::WORM);
      col = step_direction;
    }
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void Game::move(int row, int col, int steps)
{
  if ((row < board_height_ && col < board_width_)
      && map_.at(CURRENT_FIELD).getType() == Field::WORM)
  {
    bool left_steps = checkDirection(steps);
    for (int index = 0; index < steps; index++)
    {
      if (!makeMove(row, col, left_steps))
      {
        printErrorMessage(WRONG_MOVE);
        break;
      }
    }
  }
  else
  {
    printErrorMessage(INVALID_TARGET);
  }
}


//------------------------------------------------------------------------------
bool Game::userInput()
{
  string input_line;
  string param;
  vector<string> command_params;

  cout << COMMAND_PROMPT;
  getline(cin, input_line);
  stringstream input_stream(input_line);

  while(input_stream >> param)
  {
    command_params.push_back(param);
  }

  if(command_params.empty())
  {
    printErrorMessage(UNKNOWN_COMMAND);
    return false;
  }
  else if(command_params.at(0) == COMMAND_QUIT)
  {
    if(command_params.size() != 1)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }
    exit(EVERYTHING_OK);
  }
  else if(command_params.at(0) == COMMAND_MOVE)
  {
    if(command_params.size() != 3)
    {
      printErrorMessage(WRONG_PARAMETER_COUNT);
      return false;
    }

    Move move(COMMAND_MOVE);
    return move.execute(*this, command_params) == 0;
  }
  else
  {
    printErrorMessage(UNKNOWN_COMMAND);
    return false;
  }
}

void Game::setNextMove(int nextMove)
{
  next_move_ = nextMove;
}
