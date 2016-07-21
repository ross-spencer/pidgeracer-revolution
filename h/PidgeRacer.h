#ifndef PIDGERACER_H_
#define PIDGERACER_H_

#include <allegro.h>
#include "NameGenerator.h"
#include "OddsGenerator.h"
#include "Character.h"
#include "Background.h"
#include "Random.h"
#include "text.h"
#include "bang.h"
#include <alfont.h>
#include "scores.h"
#include <sstream>
#include <iomanip>

const int INIT_POS_X = 100;
const int INIT_POS_Y = 840;
const int X_INCREMENT = 90;

const int NUMBER_OF_CLOUDS = 8;

class PidgeRacer
{
   public:

      PidgeRacer(BITMAP *buffer);
      ~PidgeRacer();

      struct PidgeDetails
      {
         PidgeDetails() : selected(false) {}
         int PigeonNumber;
         Character Pigeon;
         string PidgeName;
         pair<int, int> odds;
         bool selected;
         int count;
      };

      PidgeDetails pigeon_details[NUMBER_OF_PIGEONS];

      Background bg;
      Background CloudArray[NUMBER_OF_CLOUDS];

      Bang bb;

      Random rn;

      std::string winner;

      void DrawCharacters(BITMAP *buffer);

      void SetupBackground(BITMAP *buffer);

      void SetupClouds(BITMAP *buffer);
      void DrawClouds(BITMAP *buffer);

      bool MovePlayer(BITMAP *buffer);
      void HandleReset(BITMAP *buffer);

      void DisplayBettingTable(BITMAP *buffer);

      void DisplayRacingNames(BITMAP *buffer);

      void DisplayBettingOdds(BITMAP *buffer);

      void DisplayCheckBoxes(BITMAP *buffer);

      void DisplayBettingForm(BITMAP *buffer);

      void DisplayStartRace(BITMAP *buffer);

      void TitleAndTagline(BITMAP *buffer);

      void HallOfFame(BITMAP *buffer);

      void AnotherGameOverHandler(BITMAP *buffer, BITMAP *exit_b1, BITMAP *exit_b2, BITMAP *restart_b1, BITMAP *restart_b2);

   private:

      bool bFinishLine;
      bool bPigeonSelected;
      bool bHallOfFame;

      Text text;

      std::pair <int, int> aim_vector;

      bool bMove;

      bool bSelectionComplete;
      bool bBettingComplete;

      bool bGameOver;
      bool bFavorite;

      int wallet;
      int stake;
      int winnings;

      ALFONT_FONT *f;

      BITMAP *flag;
      BITMAP *score_board;

      Scores score_values;

      //member variables to record feats in game... (may not all be necessary, TODO: cleanup lots of stuff here...
      int biggest_win;
      int no_races;
      int most_money;
};

#endif
