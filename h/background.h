//background.h
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <allegro.h>
#include "Random.h"

const int SCREEN_XX = 1280;
const int SCREEN_YY = 1024;

const int SPRITE_L_RR = 42;

const int MIN_SCROLL_XX = 5;
const int MIN_SCROLL_YY = 5;

const int SKY_BOUND_1_X = 59;       //top x boundary of sky
const int SKY_BOUND_1_Y = 39;
const int SKY_BOUND_2_X = 641;      //bottom x boundary of sky
const int SKY_BOUND_2_Y = 901;      

class Background
{

	public:
		
		Background();
		~Background();	

		void DrawBackground(BITMAP *tempBitmap);
		void RedrawSky(BITMAP *tempBitmap);

		void DrawStartLine(BITMAP *tempBitmap);
		void EraseStartLine(BITMAP *tempBitmap);

		void DrawFinishLine(BITMAP *tempBitmap);
		void EraseFinishLine(BITMAP *tempBitmap);

		void SetCloudImages(char image1[], char image2[]);

		void SetX(int newValue);
		void SetY(int newValue);

		void EraseOldSprite(BITMAP *tempBitmap);
		void DrawNewSprite(BITMAP *tempBitmap, BITMAP* spriteToDraw);

		void MoveOnY(BITMAP *tempBitmap, BITMAP *mainBitmap);

		void Show(BITMAP *mainBitmap, int x, int y);
		void Show(BITMAP *mainBitmap);

		void SetSpeed(int newspeed);

		bool CheckImages();

		int GetX();
		int GetY();

	private:

		int x;
		int y;

		int speed;

		bool cloud;
		bool cloudsDone;

		BITMAP *clouds[1][2];

		Random rn;
};

#endif
