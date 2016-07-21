#include "text.h"

/**********************************************************************
*
*  Name:    
*
*  Author:  
*
*  Purpose: 
*
**********************************************************************/
Text::Text()
{    
   edittext;                         // an empty string for editting
   iter = edittext.begin();          // string iterator
   caret  = 0;                       // tracks the text caret
   insert = true;                    // true of should text be inserted

   bDisabled = true;
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
Text::~Text()
{

}

void Text::SetText(BITMAP* buffer, int fgcol, int bgcol)
{
   // output the string to the screen
   textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXX", pos_x, pos_y, bgcol, bgcol);
   textout_ex(buffer, font, edittext.c_str(), pos_x, pos_y, fgcol, bgcol);
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
void Text::InputField(BITMAP *buffer, int field_len, int text_pos_x, int text_pos_y, int fgcol, int bgcol)
{
   pos_x = text_pos_x;
   pos_y = text_pos_y;

   if(!bDisabled)
   {
      while(keypressed())
      {
         int  newkey   = readkey();
         char ASCII    = newkey & 0xff;
         char scancode = newkey >> 8;
         
         // clear screen
         //clear(buffer);
         
         // a character key was pressed; add it to the string
         if(ASCII >= 0x30 && ASCII <= 0x39)
         {
            textprintf_ex(buffer, font, text_pos_x-55, text_pos_y+15, bgcol, bgcol, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
   
            if(caret <= field_len)
            {
              // add the new char, inserting or replacing as need be
              if(insert || iter == edittext.end())
              iter = edittext.insert(iter, ASCII);
              else
              edittext.replace(caret, 1, 1, ASCII);
   
              // increment both the caret and the iterator
              caret++;
              iter++;
            }
         }
         else if (ASCII >= 0x3A && ASCII <= 0x7E)
         {
            textprintf_ex(buffer, font, text_pos_x-55, text_pos_y+15, fgcol, bgcol, "Please, Numerical Values Only...");
         }
         // some other, "special" key was pressed; handle it here
         else
         switch(scancode)
         {
            textprintf_ex(buffer, font, text_pos_x-55, text_pos_y+15, bgcol, bgcol, "XXXXXXXXXXXXXXXXXXXXXXXXXXXX");
   
            case KEY_DEL:
            if(iter != edittext.end()) iter = edittext.erase(iter);
            break;
            
            case KEY_BACKSPACE:
            if(iter != edittext.begin())
            {
                caret--;
                iter--;
                iter = edittext.erase(iter);
            }
            break;
            
            case KEY_RIGHT:
            if(iter != edittext.end())   caret++, iter++;
            break;
            
            case KEY_LEFT:
            if(iter != edittext.begin()) caret--, iter--;
            break;
            
            case KEY_INSERT:
            if(insert) insert = 0; else insert = 1;
            break;
            
            default:
            
            break;
         }
      }
   
   
   
      // output the string to the screen
      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXX", text_pos_x, text_pos_y, bgcol, bgcol);
      textout_ex(buffer, font, edittext.c_str(), text_pos_x, text_pos_y, fgcol, bgcol);
      
      vline(buffer, ((caret*FONT_DIMENSION)+text_pos_x)+FONT_DIMENSION, text_pos_y, text_pos_y+FONT_DIMENSION, bgcol);
      vline(buffer, ((caret*FONT_DIMENSION)+text_pos_x)-FONT_DIMENSION, text_pos_y, text_pos_y+FONT_DIMENSION, bgcol);
      vline(buffer, (caret*FONT_DIMENSION)+text_pos_x, text_pos_y, text_pos_y+FONT_DIMENSION, fgcol);

   }
   else
   {
      vline(buffer, (caret*FONT_DIMENSION)+text_pos_x, text_pos_y, text_pos_y+FONT_DIMENSION, bgcol);
   }
}
