#ifndef BANG_H
#define BANG_H

#include <allegro.h>
#include "Random.h"

#include "Character.h"

class Bang
{
   public:

      Bang();
      ~Bang();

		bool SetImages(char image1[]);
      
		void DrawBang(BITMAP *tempBitmap, int x, int y);   
 
      std::pair <int, int> ResetBang();

      std::pair <int, int> return_aim() { return aim_vector; }

   private:

      bool bangdone;

      void SetVector();

      std::pair <int,int> aim_vector;     //pigoen, sky_pos

		BITMAP *bang[1][1];

      Random rng;
};

#endif
