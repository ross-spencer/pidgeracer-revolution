#include "bang.h"

/**********************************************************************
*
*  Name:    
*
*  Author:  
*
*  Purpose: 
*
**********************************************************************/
Bang::Bang()
{
   bangdone = SetImages("bang.bmp");
   SetVector();
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
Bang::~Bang()
{
   delete [] bang;
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
bool Bang::SetImages(char image1[])
{
	bang[0][0] = load_bitmap(image1, NULL);
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
void Bang::DrawBang(BITMAP *buffer, int x, int y)
{
	acquire_screen();
   draw_sprite(buffer, bang[0][0], x, y);
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
void Bang::SetVector()
{
   aim_vector.first = rng.GenerateRandom(0, 5);
   aim_vector.second = rng.GenerateRandom(FINISH_LINE+50 , FINISH_LINE+250);
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
std::pair <int,int> Bang::ResetBang()
{
   SetVector();
   return aim_vector;
}
