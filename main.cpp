//main.cpp
#include <allegro.h>
#include "PidgeRacer.h"
#include <alfont.h>

using namespace std;

BITMAP* buffer;
BITMAP* logo;
BITMAP* exit_b1;
BITMAP* exit_b2;
BITMAP* restart_b1;
BITMAP* restart_b2;
BITMAP* gameover;

/***********************************************************************
*
*  Name:    rudimentary_exit_handler(BITMAP* buffer)
*
*  Author:  Ross Spencer
*
*  Purpose: handle the exit button... needs to be better placed in
*           pidgeracer main class at some point to tidy things up
*           here...
*
**********************************************************************/
void rudimentary_button_handler(BITMAP* buffer)
{
   if((mouse_x >= 50 && mouse_x <= 80) && (mouse_y >= 950 && mouse_y <= 1000))
   {
      draw_sprite(buffer, exit_b2, 50, 950);
      
      if(mouse_b & 1)
      {
         //TODO: Write a thanks messag here... thanks for playing pidgeracer revolution.
         key[KEY_ESC] = true;
      }
   }
   else
   {
      draw_sprite(buffer, exit_b1, 50, 950);       
   }

   show_mouse(buffer);
}

/***********************************************************************
*
*  Name:    game_over_handler()
*
*  Author:  Ross Spencer
*
*  Purpose: 
*
**********************************************************************/
bool game_over_handler()
{
   bool bDone = false;

   textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXX", 920, 537, makecol(255,0,0), makecol(255, 0, 0));
   textout_ex(buffer, font, "GAME OVER!", 920, 537, makecol(0,0,0), makecol(255, 0, 0));
      
   if((mouse_x >= 830 && mouse_x <= 1100) && (mouse_y >= 520 && mouse_y <= 560))
   {
      textout_ex(buffer, font, "GAME OVER!", 920, 537, makecol(255,255,0), makecol(255, 0, 0));
   
      if(mouse_b & 1)
      {
         //glich clicking mouse here, not sure how to get rid of this...
         draw_sprite(buffer, gameover, 240, 323);
         bDone = true;
      }
   }
   
   show_mouse(buffer);

   return bDone;
}

/***********************************************************************
*
*  Name:    Setup()
*
*  Author:  Ross Spencer
*
*  Purpose: Initialization function for Main.cpp
*
**********************************************************************/
void setup_screen()
{
   //buffer = create_bitmap(1280, 1024);
   buffer = load_bitmap("bg1-256.bmp", NULL);
   logo = load_bitmap("PR.bmp", NULL);
   draw_sprite(buffer, logo, 820, 10);
   
   gameover = load_bitmap("gameover.bmp", NULL);
   exit_b1 = load_bitmap("exit1.bmp", NULL);
   exit_b2 = load_bitmap("exit2.bmp", NULL);
   draw_sprite(buffer, exit_b1, 50, 950);

   restart_b1 = load_bitmap("restart1.bmp", NULL);
   restart_b2 = load_bitmap("restart2.bmp", NULL);
   
   alfont_init();
   ALFONT_FONT *f;

   f = alfont_load_font("c:\\windows\\fonts\\arialbd.ttf");
   
   alfont_set_font_size(f, 14);   

   alfont_textout(buffer, f, "Exit", 59, 985, makecol(255,255,255));

}

/***********************************************************************
*
*  Name:    Cleanup()
*
*  Author:  Ross Spencer
*
*  Purpose: 
*
**********************************************************************/
void Cleanup()
{
   alfont_exit();
   remove_mouse(); 

   destroy_bitmap(buffer);
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
void DisplayMouseCoords()
{
   acquire_screen();
   textprintf_ex(buffer, font, 700, 895, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXX");
   textprintf_ex(buffer, font, 700, 895, makecol(255,0,0), makecol(0,0,0), "X: %d Y: %d", mouse_x, mouse_y);
   
   if(mouse_b & 1)
   {
      textprintf_ex(buffer, font, 700, 910, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXX");
      textprintf_ex(buffer, font, 700, 910, makecol(255,0,0), makecol(0,0,0), "left button pressed", mouse_x, mouse_y);
   }
   else if(mouse_b & 2)
   {
      textprintf_ex(buffer, font, 700, 910, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXX");
      textprintf_ex(buffer, font, 700, 910, makecol(255,0,0), makecol(0,0,0), "right button pressed", mouse_x, mouse_y);
   }
   else
   {
      textprintf_ex(buffer, font, 700, 910, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXX");
   }

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
int main(int argc, char *argv[])
{
	allegro_init(); 
	install_keyboard(); 

   //always do before displaying a mouse pointer...
	install_timer();

	install_mouse(); 
	
	set_color_depth(32);   //note: seems to be performance impact at lower color depths...

   // SOUND ROUTINE... 
   /*install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
   MIDI *music = load_midi("pidgeracer.mid");
   play_midi(music, TRUE);*/

   int screen_width, screen_height;   //same as SCREEN_W and SCREEN_H??
   get_desktop_resolution(&screen_width, &screen_height);

   //set origin
   const int BITMAP_WIDTH = 1280;
   const int BITMAP_HEIGHT = 1024;
   
   int origin_x = (screen_width - BITMAP_WIDTH) / 2;
   int origin_y = (screen_height - BITMAP_HEIGHT) / 2;

	if(!set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screen_width, screen_height, 0, 0))
   {
      set_display_switch_mode(SWITCH_PAUSE);
 
      setup_screen();
      
      //need to handle larger screen sizes...
      //textprintf_ex(buffer, font, 10, 10, makecol(255,0,0), makecol(0,0,0), "Origin: %i, %i", origin_x, origin_y);
 
      enable_hardware_cursor();
      select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
      
      PidgeRacer pr(buffer);
      
      pr.DrawClouds(buffer);
      
      pr.DrawCharacters(buffer);
      
      //handle the output of pigeon names and odds...
      pr.DisplayBettingTable(buffer);
      pr.DisplayRacingNames(buffer);
      pr.DisplayBettingOdds(buffer);
      
      Background bg;
      bg.DrawStartLine(buffer);
      
      show_mouse(buffer);
      
      bool bGameOver = false;
      bool bScreen = false;

      while(!key[KEY_ESC])
      {  
         if(!bGameOver)
         {
            pr.DisplayCheckBoxes(buffer);
            pr.DisplayBettingForm(buffer);
            pr.DisplayStartRace(buffer);
            pr.TitleAndTagline(buffer);
            pr.HallOfFame(buffer);
            bGameOver = pr.MovePlayer(buffer);
         }
  
         if(bGameOver && !bScreen)
         {
            bScreen = game_over_handler();
         }

         if(!bScreen)
         {
            rudimentary_button_handler(buffer);
         }

         if(bScreen)
         {
            pr.AnotherGameOverHandler(buffer, exit_b1, exit_b2, restart_b1, restart_b2);
         }

         blit(buffer, screen, 0, 0, origin_x, origin_y, SCREEN_W, SCREEN_H);
      }
      
      Cleanup();
   }

   //destroy_midi(music);

	return 0;
}
END_OF_MAIN();
