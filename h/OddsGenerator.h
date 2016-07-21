#ifndef ODDSGENERATOR_H_
#define ODDSGENERATOR_H_

#include "time.h"
#include "stdlib.h"
#include <limits.h>
#include <utility>
#include "Random.h"

using namespace std;

const int NUMBER_OF_RACES = 100;

class OddsGenerator
{
   public:

      OddsGenerator();
      ~OddsGenerator();
      pair<int,int> GenerateOdds();

   private:

      int round(double x);

      unsigned time_seed();   //time_seed() thanks to eternally confuzzled tutorial

      Random rn;
};

#endif
