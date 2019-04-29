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
#include "Chest.h"
#include "Random.h"
#include <map>
#include <vector>


namespace Sep
{
  //----------------------------------------------------------------------------
  // Game Class
  // class to build the Playground
  //
  class Game
  {
    public:


      static const int MAX_DIGITS = 2;
      static const int MAX_STEPS = 3;
      static const int NUMBER_OF_WEAPONS = 5;
      static const int MIN_LENGTH = 10;
      static const int MAX_LENGTH = 80;

      static const std::string MAGIC_VALUE;
      static const std::string CHECK_FOR_SIZE;
      static const std::string CHECK_FOR_MAP;

      static const std::string COMMAND_PROMPT;
      static const std::string COMMAND_MOVE;
      static const std::string COMMAND_QUIT;
      static const std::string COMMAND_ACTION;
      static const std::string COMMAND_HELP;
      static const std::string COMMAND_STATE;
      static const std::string COMMAND_MAP;
      static const std::string COMMAND_CHOOSE;

      static const std::string GUN;
      static const std::string BAZOOKA;
      static const std::string TELEPORT;
      static const std::string BLOWTORCH;
      static const std::string MELEE;
      static const std::string AIRSTRIKE;


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

      //------------------------------------------------------------------------
      // Print Gameboard Method
      // Prints the playground on the screen.
      //
      void printMap();

      int gameLoop();

      int chooseWeapon(int current_worm, std::vector<std::string> &params);

      int getBoardWidth();

      int getBoardHeight();

      void actionCommand(int current_worm,  int current_weapon, int damage);

      void actionDirectionCommand(int current_worm, int current_weapon, int damage, int direction);

      void actionColCommand(int current_worm, int current_weapon, int damage, int col);

      bool actionRowColCommand(int current_worm, int current_weapon, int row, int col);

      std::vector<Sep::Worm> getWormNumber();


    private:

      //------------------------------------------------------------------------
      // Variable for determining the latitude of the gameboard
      //
      int board_width_;

      //------------------------------------------------------------------------
      // Variable for determining the longitude of the gameboard
      //
      int board_height_;

      //------------------------------------------------------------------------
      // Datastructure for objects on the gameboard
      //
      std::map<int, Field> map_;

      std::vector<Worm> wormNumber;

      std::vector<Chest*> chest_Number_;


      enum ErrorType
      {
          EVERYTHING_OK,
          INVALID_CONFIGFILE = -1,
          INVALID_TARGET = -2,
          WRONG_MOVE = -3,
          UNKNOWN_COMMAND = -4,
          WRONG_PARAMETER_COUNT = -5,
          INVALID_PARAMETER = -6,
          COMMAND_NOT_ALLOWED = -7,
          NO_AMMUNITION = -8
      };

      enum DeathCases
      {
          DROWNED,
          FELL,
          OUT_OF_MAP,
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
      bool createMapFields(std::string keyword, int row);

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

      void findChest(int row, int col, int current_worm);

      bool checkOneParameterCommand(std::vector<std::string> command_params, int current_worm, int &move_command);

      bool checkMoreParameterCommand(std::vector<std::string> command_params, int current_worm, int &move_command);

      int findWorm(int row, int col);

      bool gravity(int current_worm, int &row, int col);

      //------------------------------------------------------------------------
      // User Input Method
      // Reads commands from stdin and calls command pattern.
      //
      bool userInput( int current_worm, int &move_command);
  };
}
#endif //SEP_GAME_H
