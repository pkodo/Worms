//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
//------------------------------------------------------------------------------
//
#ifndef SEP_GAME_H
#define SEP_GAME_H
#include "Field.h"
#include "Worm.h"
#include "Random.h"
#include <map>
#include <vector>
using std::string;


namespace Sep
{
  //----------------------------------------------------------------------------
  // Game Class
  // class to build the Playground
  //
  class Game
  {
    public:

      static const int ONE = 1;
      static const int MAX_DIGITS = 2;
      static const int MAX_STEPS = 3;
      static const int MIN_LENGTH = 10;
      static const int MAX_LENGTH = 80;

      static const string MAGIC_VALUE;
      static const string CHECK_FOR_SIZE;
      static const string CHECK_FOR_MAP;

      static const string COMMAND_PROMPT;
      static const string COMMAND_MOVE;
      static const string COMMAND_QUIT;


      //------------------------------------------------------------------------
      // Constructor
      //
      Game();

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Game Object. Is set to delete.
      // @param game object to copy.
      //
      Game(Game& game) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Game object to another. Is set to delete.
      // @param game Original with values to copy.
      //
      Game& operator=(Game& game) = delete;

      //------------------------------------------------------------------------
      // Load configuration file Method
      // Opens a text file and reads its input. Checks for errors.
      // @param cfg_file String of an argument to open.
      // @return Returns error or everything okay.
      //
      int loadConfig(std::string cfg_file);

      //------------------------------------------------------------------------
      // Add Worm Method
      // Adds a worm on a given field on the playground.
      // @param row defines in which row the worm should occur.
      // @param col defines in which column the worm should occur.
      // @return Returns error or everything okay.
      //




      //------------------------------------------------------------------------
      // Move Method
      // Checks step by step if a worm can make the given move.
      // @param row defines the position of the worm that should move.
      // @param col defines the position of the worm that should move.
      // @param steps determines how many steps the worm should take and in
      // which direction
      //
      void move(int row, int col, int steps, int current_worm);

      int gameLoop();

      void setNextMove(int nextMove);

    private:

      //------------------------------------------------------------------------
      // Variable for determining the latitude of the gameboard
      //
      int board_width_;

      //------------------------------------------------------------------------
      // Variable for determining the longitude of the gameboard
      //
      int board_height_;

      int next_move_;

      //------------------------------------------------------------------------
      // Datastructure for objects on the gameboard
      //
      std::map<int, Field> map_;

      std::vector<Worm> wormNumber;


      enum ErrorType
      {
          EVERYTHING_OK,
          INVALID_CONFIGFILE = -1,
          INVALID_TARGET = -2,
          WRONG_MOVE = -3,
          UNKNOWN_COMMAND = -4,
          WRONG_PARAMETER_COUNT = -5
      };

      enum DeathCases
      {
          DROWNED,
          FELL,
          OUTOFMAP,
          DIED
      };

      enum ConfigKeywords
      {
          SIZE,
          MAP,
          MAPFIELDS
      };

      //------------------------------------------------------------------------
      // Print Error Messages Method
      // Prints an error message on the screen, if an error occurs.
      // @param type defines the type of the error
      // @return Returns error type.
      //
      ErrorType printErrorMessage(ErrorType type);

      void printDeathCases(DeathCases type, int current_worm);

      //------------------------------------------------------------------------
      // Create Fields Method
      // Creates the various fields read from the input file and safes them in
      // in a map.
      // @param keyword String of different characters describing a field.
      // @param row counts in which row the fields should be..
      // @return true or false.
      //
      bool createMapFields(string keyword, int row);

      //------------------------------------------------------------------------
      // Check direction Method
      // Checks direction of the steps
      // @param steps shows how many steps should be done.
      // @return true for left steps and false for right steps.
      //
      bool checkDirection(int &steps);

      //------------------------------------------------------------------------
      // Make a move Method
      // Gets called for each step that is taken and checks the move
      // possibilities. If a move is valid, the method executes it.
      // @param row defines the position of the worm that should move.
      // @param col defines the position of the worm that should move.
      // @param left_steps is true if the user wants to take steps in the left
      // direction
      // @return true if the move is valid and executed.
      //
      bool makeMove(int &row, int &col, bool left_steps, int current_worm);

      //------------------------------------------------------------------------
      // Worm Tower Method
      // Makes a test if a "worm tower" has occured
      // @param row defines the position of the worm.
      // @param col defines the position of the worm.
      // @param detect_worm_tower saves the original value of the row.
      //
      void testWormTower(int &row, int &col, int &detect_worm_tower, int current_worm);

      void createWorms(Random *random);

      int setPlayerAndWorm(int &current_worm, int &player, int& turn_one, int& turn_two);

      void createChest(Random *random);

      //------------------------------------------------------------------------
      // Print Gameboard Method
      // Prints the playground on the screen.
      //
      void printMap();

      //------------------------------------------------------------------------
      // User Input Method
      // Reads commands from stdin and calls command pattern.
      //
      bool userInput();
  };
}
#endif //SEP_GAME_H
