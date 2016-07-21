//Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#include <allegro.h>
#include <boost/random/mersenne_twister.hpp>

const int SCREEN_X = 1280;
const int SCREEN_Y = 1024;

const int SPRITE_L_R = 40;

const int MIN_SCROLL_X = 5;
const int MIN_SCROLL_Y = 5;
const int MAX_SCROLL_X = SCREEN_X - 300;
const int MAX_SCROLL_Y = SCREEN_Y - 300;

const int FINISH_LINE = MIN_SCROLL_Y + 48;

class Character
{

	public:

		Character();
		~Character();
       
		//To keep the program from crashing, this function will be used before 
		//calling any movement methods
		bool CheckImages();

      //TODO: delete, quick and dirty, unecessary variable. 
      bool exploded;           

		int GetX();
		void SetX(int newValue);
		void MoveOnX(int newValue, BITMAP *tempBitmap, BITMAP *mainBitmap);
       
		int GetY();
		void SetY(int newValue);
		void MoveOnY(BITMAP *tempBitmap, BITMAP *mainBitmap);
       
		void EraseOldSprite(BITMAP *tempBitmap);
		void DrawNewSprite(BITMAP *tempBitmap, BITMAP *spriteToDraw);  

		void Show(BITMAP *mainBitmap, int x, int y);        

      int GetSpeed() {return speed;}
		void SetSpeed(int newspeed);

	private:

		bool upDone;
         
  
		int direction;
        
		int x;
		int y;

		int speed;
        
		//This will contain all the images, [0][0-2] will be left movements, [1][0-2] right
		//[2][0-2] upwards, and [3][0-2] downwards
		BITMAP *images[1][3];

		int SetImagesUp(char image1[], char image2[], char image3[]);

};

#endif


