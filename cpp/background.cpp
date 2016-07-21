//background.cpp

#include "Background.h"

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
Background::Background()
{
	cloud = rn.GenerateBernoulli();
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
Background::~Background()
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
void Background::DrawBackground(BITMAP *buffer)
{
	acquire_screen();
	rect(buffer, SKY_BOUND_1_X, SKY_BOUND_1_Y, SKY_BOUND_2_X, SKY_BOUND_2_Y, makecol(255, 255, 255));
	rectfill(buffer, 60, 40, 640, 900, SKY_COLOR);
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
void Background::RedrawSky(BITMAP *buffer)
{
	acquire_screen();
	rectfill(buffer, 60, 40, 640, 900, SKY_COLOR);
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
void Background::DrawStartLine(BITMAP *buffer)
{
   acquire_screen();
	line(buffer, 60, 830, 640, 830, makecol(255, 255, 255));
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
void Background::EraseStartLine(BITMAP *buffer)
{
	acquire_screen();
	line(buffer, 60, 830, 640, 830, makecol(0, 0, 0));
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
void Background::DrawFinishLine(BITMAP *buffer)
{
	acquire_screen();
	line(buffer, 60, 5+90, 640, 5+90, makecol(255, 255, 255));
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
void Background::EraseFinishLine(BITMAP *buffer)
{
	acquire_screen();
	line(buffer, 60, 5+90, 640, 5+90, makecol(0, 0, 0));
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
void Background::SetCloudImages(char image1[], char image2[])
{
	clouds[0][0] = load_bitmap(image1, NULL);
	clouds[0][1] = load_bitmap(image2, NULL);
	cloudsDone = true;
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
bool Background::CheckImages()
{
	return cloudsDone;
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
int Background::GetX()
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
int Background::GetY()
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
void Background::SetX(int newValue)
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
void Background::SetY(int newValue)
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
void Background::MoveOnY(BITMAP *buffer, BITMAP *screen)
{
	if(CheckImages())
	{      
		EraseOldSprite(buffer);
   
		if (y <= SKY_BOUND_2_Y - SPRITE_L_RR - 20) 
		{    
			y -= speed;
		}
		else
		{
			SetX(rn.GenerateRandom(SKY_BOUND_1_X + 4, SKY_BOUND_2_X - SPRITE_L_RR - 4));
			SetY(SKY_BOUND_1_Y + 4);
		}

		DrawNewSprite(buffer, clouds[0][cloud]);
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
void Background::EraseOldSprite(BITMAP *buffer)
{
	acquire_screen();
	rectfill(buffer, GetX(), GetY(), GetX() + SPRITE_L_RR, GetY() + SPRITE_L_RR, SKY_COLOR);
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
void Background::DrawNewSprite(BITMAP *buffer, BITMAP* sprite)
{
	acquire_screen();
	draw_sprite(buffer, sprite, GetX(), GetY());
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
void Background::SetSpeed(int newspeed)
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
void Background::Show(BITMAP *screen, int x, int y)
{
	if(CheckImages())
	{
		draw_sprite(screen, clouds[0][rn.GenerateBernoulli()], x, y);
		SetX(x);
		SetY(y);
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
void Background::Show(BITMAP *screen)
{
	if(CheckImages())
	{
		draw_sprite(screen, clouds[0][cloud], GetX(), GetY());
	}
}
