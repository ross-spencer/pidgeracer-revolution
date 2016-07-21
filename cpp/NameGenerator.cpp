#include "NameGenerator.h"

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
NameGenerator::NameGenerator()
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
NameGenerator::~NameGenerator()
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
unsigned NameGenerator::time_seed()
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
string NameGenerator::GenerateName(int seed)
{
   string n1[N1_TOTAL] = {"Frankie", "Char-izard", "Cobra", "Samurai", "Wu-tang", "Katzenjammer", "Yojimbo", "Usagi", "Mafia", "Mercury", "Mr", "Mustang", "Cowabunga", "Tank", "Blitzkrieg", "Hitman", "Bad"};
   string n2[N2_TOTAL] = {"Donuts", "", "Roadrunner", "Napoleon", "Max", "Dynamite", "Whoopie", "Persephone", "Aphrodite", "Guard", "Buzz", "Electric", "Jazz", "Girl", "Blitz", "Hart", "Boy"};

   string o1, o2, output;

   o1 = n1[rand() % N1_TOTAL];  
   o2 = n2[rand() % N2_TOTAL];

   output = o1 + " " + o2;

   return output;
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
vector<string> NameGenerator::NameList(int list_size)
{
   vector<string> names;
   string temp_name;

   temp_name = GenerateName();

   names.push_back(temp_name);

   int collected_names = names.size(); 

   for(int i = 1; i < list_size; i++)
   {
      for(int j = 0; j < min(list_size, collected_names); j++)
      {
         if(temp_name == names.at(j))
         {
            temp_name = GenerateName(j+time(NULL));   
            j = 0;
         }  
      }
      
      names.push_back(temp_name);
      collected_names = names.size();  
   }

   return names;
}
