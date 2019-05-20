//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
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
#include <memory>

using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

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
      static const int NUMBER_OF_WEAPONS = 5;
      static const int MIN_LENGTH = 10;
      static const int MAX_LENGTH = 80;
      static const int BLOWTORCH_DAMAGE = 35;
      static const int CHECK_LEFT = -1;
      static const int CHECK_RIGHT = 1;
      static const int CHECK_ROW = 1;
      static const int CHECK_LEFT_UP = 1;
      static const int CHECK_LEFT_DOWN = -1;
      static const int CHECK_RIGHT_UP = -1;
      static const int CHECK_RIGHT_DOWN = 1;
      static const int BLOWTORCH_INT = 3;
      static const int GUN_INT = 0;
      static const int BAZOOKA_INT = 1;



      static const string MAGIC_VALUE;
      static const string CHECK_FOR_SIZE;
      static const string CHECK_FOR_MAP;

      static const string COMMAND_PROMPT;
      static const string COMMAND_MOVE;
      static const string COMMAND_QUIT;
      static const string COMMAND_ACTION;
      static const string COMMAND_HELP;
      static const string COMMAND_STATE;
      static const string COMMAND_MAP;
      static const string COMMAND_CHOOSE;
      static const string COMMAND_PLAY;
      static const string COMMAND_WHOAMI;

      static const string GUN;
      static const string BAZOOKA;
      static const string TELEPORT;
      static const string BLOWTORCH;
      static const string MELEE;
      static const string AIRSTRIKE;

      static const string SHOT_MISSED;
      static const string TORCH;
      static const string SHOT;
      static const string TOOK;
      static const string TOOK_ACTION;
      static const string HP_FALL_DAMAGE;
      static const string HP_DAMAGE;
      static const string ATTACK_HIT_WORM;
      static const string BRACKET_1;
      static const string BRACKET_2;
      static const string COMMA;

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
      int loadConfig(const string& cfg_file);

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

      //------------------------------------------------------------------------
      // gameLoop Method
      // implement the game logic and it sets the basic stats for the game logic
      //
      int gameLoop();

      //------------------------------------------------------------------------
      // choose Weapon Method
      // choose the weapon and check for monition
      // @param current worm   number of the current worms
      // @param params    the vector whrere the weapons are stored
      //
      int chooseWeapon(int current_worm, vector<string>& params);

      //------------------------------------------------------------------------
      // Getter Method
      // get the board_width_
      //
      int getBoardWidth();

      //------------------------------------------------------------------------
      // Getter Method
      // get the board_height_
      //
      int getBoardHeight();

      //------------------------------------------------------------------------
      // actionCommand Method
      // function for MELEE
      // @param current_worm  describes the number of the current worms
      // @param current_weapon describes the number of the current weapon_number
      // @param damage is used for damage calulations
      void actionCommand(int current_worm,  int current_weapon, int damage);

      //------------------------------------------------------------------------
      // actionDirectionCommand Method
      // function for the use of the different weapons
      // @param current_worm  describes the number of the current worms
      // @param current_weapon describes the number of the current weapon_number
      // @param damage is used for damage calulations
      // @param direction is the number of the direction
      void actionDirectionCommand(int current_worm, int current_weapon,
                                  int damage, int direction);

      //------------------------------------------------------------------------
      // actionColCommand Method
      // @param current_worm  describes the number of the current worms
      // @param current_weapon describes the number of the current weapon_number
      // @param damage is used for damage calulations
      // @param col   is the number of the column
      void actionColCommand(int current_worm, int current_weapon,
                            int damage, int col);

      //------------------------------------------------------------------------
      // actionRowColCommand Method
      // @param current_worm  describes the number of the current worms
      // @param current_weapon describes the number of the current weapon_number
      // @param damage is used for damage calulations
      // @param col   is the number of the column
      bool actionRowColCommand(int current_worm, int current_weapon,
                               int row, int col);

      //------------------------------------------------------------------------
      // Getter Method
      // get the number of the worms
      //
      vector<Sep::Worm> getWormNumber();

      //------------------------------------------------------------------------
      // Setter Method
      // sets the variable for determing the game
      //
      void setQuit(bool quit);

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
      // Variable for determining the end of the game
      //
      bool quit_;

      //------------------------------------------------------------------------
      // Datastructure for objects on the gameboard
      //
      map<int, Field> map_;

      //------------------------------------------------------------------------
      // Datastructure for weapon objects
      //
      vector<Worm> wormNumber;

      //------------------------------------------------------------------------
      // Datastructure for chest objects
      //
      vector<shared_ptr<Chest>> chest_Number_;

      //------------------------------------------------------------------------
      // Enums for the various error types
      //
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
          NO_AMMUNITION = -8,
          MEMORY_ERROR = -9,
          END_GAME = -10
      };

      //------------------------------------------------------------------------
      // Enums for the various death types
      //
      enum DeathCases
      {
          DROWNED,
          FELL,
          OUT_OF_MAP,
          DIED
      };

      //------------------------------------------------------------------------
      // Enums for the various config file words
      //
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

      //------------------------------------------------------------------------
      // Print Death Messages Method
      // Prints death message on the screen, if a worm dies.
      // @param type defines the type of the error
      // @param current_worm defines the dying worm
      //
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
      static bool checkDirection(int& steps);

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
      bool makeMove(int& row, int& col, bool left_steps, int current_worm);

      //------------------------------------------------------------------------
      // Checks through vector with worm numbers for gravity
      //
      // @param random object that creates name and position of the worm
      //
      void wormGravityCheck();


      //------------------------------------------------------------------------
      // Create Worms
      // Creates worms randomly on the board
      // @param random object that creates name and position of the worm
      //
      void createWorms(Random* random);

      //------------------------------------------------------------------------
      // Gamelogic
      // Sets which player and which worm has its next turn
      // @param current_worm sets the worm for the next turn
      // @param player sets the player for the next turn
      // @param turn_one counts turns of player one
      // @param turn_two counts turns of player two
      // @return next worm and next turn
      //
      int setPlayerAndWorm(int& current_worm, int& player, int& turn_one,
        int& turn_two);

      //------------------------------------------------------------------------
      // Create Worms
      // Creates worms randomly on the board
      // @param random object that creates name and position of the worm
      //
      bool createChest(Random* random);

      //------------------------------------------------------------------------
      // Find Chest
      // Searches through all chest objects for a chest on the given position
      // @param row defines the position of the chest.
      // @param col defines the position of the chest.
      // @param current_worm defines the worm who gathers in the chest
      //
      void findChest(int row, int col, int current_worm);

      //------------------------------------------------------------------------
      // Check one parameter
      // Check all commands from user input with one parameter
      // @param command_params describes the vector where the input is stored
      // @param current_worm defines the currently played worm.
      // @param move_command checks if a move has been done before
      //
      bool checkOneParameterCommand(vector<string> command_params,
        int current_worm, int& move_command);

      //------------------------------------------------------------------------
      // Check more parameters
      // Check all commands from user input with more than one parameter
      // @param command_params describes the vector where the input is stored
      // @param current_worm defines the currently played worm.
      // @param move_command checks if a move has been done before
      //
      bool checkMoreParameterCommand(vector<string> command_params,
        int current_worm, int& move_command);

      //------------------------------------------------------------------------
      // Find Worm
      // Searches through all Worm objects for a worm on the given position
      // @param row defines the position of the chest.
      // @param col defines the position of the chest.
      // @return returns current worm
      //
      int findWorm(int row, int col);

      //------------------------------------------------------------------------
      // Gravity
      // Searches through all Worms and checks for gravity among them
      // @param current_worm defines the currently played worm.
      // @param row defines the position of the chest.
      // @param col defines the position of the chest.
      //
      bool gravity(int current_worm, int& row, int col);

      //------------------------------------------------------------------------
      // Check Winner
      // Checks hp of the worms of each player and ends the game is one team
      // has no more worms with hp larger than zero.
      // @return returns if someone has won
      //
      int checkWinner();

      //------------------------------------------------------------------------
      // Blowtorch
      // Executes the blowtorch command
      // @param current_worm defines the currently played worm.
      // @param damamge defines the damage of the weapon.
      // @param direction defines the direction of the torch.
      // @param current_weapon defines the currently used weapon.
      //
      void blowtorchCommand(int current_worm, int damage, int direction,
        int current_weapon);

      //------------------------------------------------------------------------
      // ChestGravity
      // Searches through all chest objects and checks for gravity among them
      //
      void chestGravity();

      //------------------------------------------------------------------------
      // Damage
      // Causing damage to a given field
      // @param row defines the position of the chest.
      // @param col defines the position of the chest.
      // @param damamge defines the damage of the weapon.
      //
      void makeDamage(int row, int col, int damage);

      //------------------------------------------------------------------------
      // User Input Method
      // Reads commands from stdin and calls command pattern.
      // @param current_worm defines the currently played worm.
      // @param move_command checks if a move has been done before
      //
      bool userInput(int current_worm, int& move_command);

      //------------------------------------------------------------------------
      // Find a target
      // Increase row and col in one direction until a target is hit
      // @param row defines the position of the chest.
      // @param col defines the position of the chest.
      // @param direction defines the direction of the shot.
      //
      bool findTarget(int& row, int& col, int direction);

      //------------------------------------------------------------------------
      // Find the current field
      // calculates the current field index
      // @param row defines the position of the field.
      // @param col defines the position of the field.
      //
      int currentField(int row, int col);

      //------------------------------------------------------------------------
      // Find the field below the current field
      // calculates the field index
      // @param row defines the position of the field.
      // @param col defines the position of the field.
      //
      int belowCurrentField(int row, int col);

      //------------------------------------------------------------------------
      // Find the field above the current field
      // calculates the field index
      // @param row defines the position of the field.
      // @param col defines the position of the field.
      //
      int aboveCurrentField(int row, int col);

      //------------------------------------------------------------------------
      // Find a target
      // calculates the target field
      // @param row defines the row of the target.
      // @param step_direction defines the direction of the shot.
      //
      int targetField(int row, int step_direction);

      //------------------------------------------------------------------------
      // Find above target field
      // calculates the field above the target
      // @param row defines the row of the target.
      // @param step_direction defines the direction of the shot.
      //
      int aboveTargetField(int row, int step_direction);
  };
}
#endif //SEP_GAME_H
