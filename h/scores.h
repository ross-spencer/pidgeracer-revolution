#ifndef SCORES_H_
#define SCORES_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct score_row
{
   score_row(){};
   score_row(string c_name, float c_races, float c_wins)
   {
      name=c_name;
      races=c_races;
      wins=c_wins;
      active=false;
      percent=0;
   }
   string name;
   short index;      //zero to six, represents racing pigeon index
   bool active;
   float races;      //precision set at float to avoid casting later (Id est quod id est)
   float wins;       //precision set at float to avoid casting later
   float percent;
}; 

const int NUMBER_OF_PIGEONS = 6;
const int MAX_SCOREBOARD = 12;

class Scores
{
   public:

      Scores();
      ~Scores();

      bool WriteScores();
      bool ReadScores();

      int row_count() { return score_rows.size(); }
 
      void make_active(short pidge_index, int stat_index);
      void add_new(score_row row_data);
      void update_stats(short pidge_index);

      double calculate_percent();

      score_row read_row_data(int pos);
    
   private:

      static bool stat_sort(score_row const& a, score_row const& b) { return a.percent > b.percent; }

      void scores_sort() { sort(score_rows.begin(), score_rows.end(), stat_sort); }

      vector<score_row>score_rows;

};

#endif
