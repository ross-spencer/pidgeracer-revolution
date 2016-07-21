//Character.cpp
#include "Character.h"

const int SKY_COLOR = makecol(8,6,45);

/**********************************************************************
*
*  Name:    
*
*  Author:  
*
*  Purpose: 
*
**********************************************************************/
Character::Character()
{       
	x = 0;
	y = 0;

   upDone = SetImagesUp( "up1.bmp", "up2.bmp", "up3.bmp");

   exploded = false;
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
Character::~Character()
{
	delete [] images;
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
void Character::SetSpeed(int newspeed)
{
	speed = newspeed;
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
int Character::SetImagesUp(char image1[], char image2[], char image3[])
{
	images[0][0]= load_bitmap(image1, NULL);
	images[0][1]= load_bitmap(image2, NULL);
	images[0][2]= load_bitmap(image3, NULL);
   
   return true;
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
bool Character::CheckImages()
{
	return upDone;                         
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
int Character::GetX()
{
	return x;
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
int Character::GetY()
{
	return y;
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
void Character::SetX(int newValue)
{
	x = newValue;
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
void Character::SetY(int newValue)
{
	y = newValue;
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
void Character::MoveOnY(BITMAP *buffer, BITMAP *screen)
{
	if(CheckImages())		// needs to go somewhere else, modify constructor maybe...
	{      
		//EraseOldSprite(buffer);

		if (y >= FINISH_LINE) 
		{    
			y -= speed;
		}
             
		//DrawNewSprite(buffer, images[0][0]);
	}
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
void Character::EraseOldSprite(BITMAP *buffer)
{
	acquire_screen();
	rectfill(buffer, GetX(), GetY(), GetX() + SPRITE_L_R, GetY() + SPRITE_L_R, SKY_COLOR);
	release_screen();
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
void Character::DrawNewSprite(BITMAP *buffer, BITMAP* sprite)
{
	acquire_screen();
	draw_sprite(buffer, images[0][0], GetX(), GetY());
	release_screen();
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
void Character::Show(BITMAP *screen, int x, int y)
{
	if(CheckImages())
	{
		draw_sprite(screen, images[0][0], x, y);
		SetX(x);
		SetY(y);
	}
}
