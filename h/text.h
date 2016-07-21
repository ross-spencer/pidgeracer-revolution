#ifndef TEXT_H
#define TEXT_H

#include <allegro.h>
#include <string>
using namespace std;

const int FONT_DIMENSION = 8;

class Text
{
   public:
   
      Text();
      ~Text();

      void InputField(BITMAP *buffer, int field_len, const int text_pos_x, const int text_pos_y, int fgcol, int bgcol);
      void SetText(BITMAP* buffer, int fgcol, int bgcol);

      string OutputValue() { return edittext; }

      void DisableInput() { bDisabled = true; } 
      void EnableInput() { bDisabled = false; } 

   private:

      string  edittext;                   // an empty string for editting
      string::iterator iter;              // string iterator
      
      int caret;                      // tracks the text caret
      
      bool insert;                     // true of should text be inserted
      bool bDisabled;

      int pos_x;
      int pos_y;
};

#endif
