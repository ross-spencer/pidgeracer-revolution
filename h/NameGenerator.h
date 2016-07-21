#ifndef NAMEGENERATOR_H_
#define NAMEGENERATOR_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int N1_TOTAL = 17;
const int N2_TOTAL = 17;

class NameGenerator
{
   public:

      NameGenerator();
      ~NameGenerator();

      vector<string> NameList(int list_size); 

   private:

      string GenerateName(int seed=0);

      unsigned NameGenerator::time_seed();
};

#endif
