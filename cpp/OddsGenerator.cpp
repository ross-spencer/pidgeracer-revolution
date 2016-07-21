#include "OddsGenerator.h"

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
OddsGenerator::OddsGenerator()
{
   srand(time_seed());
}

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
OddsGenerator::~OddsGenerator()
{

}

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
unsigned OddsGenerator::time_seed()
{      
   time_t now = time ( 0 );
   
   unsigned char *p = (unsigned char *)&now;
   unsigned seed = 0;
   
   size_t i;

   for ( i = 0; i < sizeof now; i++ ) 
   {
      seed = seed * ( UCHAR_MAX + 2 ) + p[i];   //uchar_max maximum value for object of type unsigned char
   }                                          
   
   return seed;
}

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
int OddsGenerator::round(double x)
{
   x+=0.5;
   return (int)x;
}

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
pair<int,int> OddsGenerator::GenerateOdds()
{ 
   int races = NUMBER_OF_RACES;
   double wins;
   double loses;

   double odds;

   pair<int, int> complete_odds;

   do    //kinda do a monte carlo, slices until gets odds under 100 
   {                           
      wins = rn.GenerateRandom(1, 5000);
   } 
   while (wins < 1 || 99 < wins);
   
   double prob = wins / 100;
   double over = prob / (1-prob);

   if(over < 1)
   {
      //odds against...
      complete_odds.second = 1;
      complete_odds.first = static_cast<int>(1/over);
   } 
   else
   {
      //odds on...
      complete_odds.first = 1;
      complete_odds.second = round(over);
   }

   return complete_odds;
}
