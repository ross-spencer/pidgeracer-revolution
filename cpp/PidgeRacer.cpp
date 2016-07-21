#include "PidgeRacer.h"

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
PidgeRacer::PidgeRacer(BITMAP *buffer)
{
   bFinishLine = false;
   bPigeonSelected = false;

	SetupBackground(buffer);
	SetupClouds(buffer);

   aim_vector = bb.return_aim();

   bMove = false;

   bSelectionComplete = false;
   bBettingComplete = false;
   bHallOfFame = false;

   wallet = 1000;
   stake = 0;
   winnings = 0;

   flag = load_bitmap("flag.bmp", NULL);

   alfont_init();
   f = alfont_load_font("c:\\windows\\fonts\\arialbd.ttf");

   score_board = load_bitmap("bg2-sect.bmp", NULL);

   bGameOver = false;

   biggest_win = 0;
   no_races = 0;
   most_money = wallet;

   //initialize selection count...
	for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
	{
      pigeon_details[i].count = 0;
   }

   bFavorite = false;
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
PidgeRacer::~PidgeRacer()
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
void PidgeRacer::DrawCharacters(BITMAP *buffer)
{
	int x_increment_temp = 0;
	for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
	{
      pigeon_details[i].PigeonNumber = i;
   
		pigeon_details[i].Pigeon.Show(buffer, x_increment_temp+INIT_POS_X, INIT_POS_Y);

      textprintf_ex(buffer, font, (x_increment_temp+INIT_POS_X)+10, INIT_POS_Y+80, makecol(255, 0, 0), makecol(0, 0, 0), "#%d", i+1);

      pigeon_details[i].Pigeon.SetSpeed(rn.GenerateRandom());		//prob need to mod to add NUMBER_OF_PIGEONS arg

		x_increment_temp += X_INCREMENT;
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
void PidgeRacer::SetupBackground(BITMAP *buffer)
{
	bg.DrawBackground(buffer);
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
void PidgeRacer::SetupClouds(BITMAP *buffer)
{
	for(int i = 0; i < NUMBER_OF_CLOUDS; i++)
	{
		CloudArray[i].SetCloudImages("cloud1.bmp", "cloud2.bmp");
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
void PidgeRacer::DrawClouds(BITMAP *buffer)
{
	for(int i = 0; i < NUMBER_OF_CLOUDS; i++)
	{
      //36 x 25 cloud, + 36+5 x, + 25+5 y
      int x = rn.GenerateRandom(SKY_BOUND_1_X+SPRITE_L_RR, SKY_BOUND_2_X-SPRITE_L_RR);
      int y = rn.GenerateRandom(SKY_BOUND_1_Y+SPRITE_L_RR, SKY_BOUND_2_Y-SPRITE_L_RR);

      for(int j = 0; j < i; j++)
      {
         int jX = CloudArray[j].GetX();

         if((x - jX) < 40 && (x - jX) > 0)
         {
            x = rn.GenerateRandom(SKY_BOUND_1_X+SPRITE_L_RR, SKY_BOUND_2_X-SPRITE_L_RR);
            j = 0;
         }
      }

      for(int k = 0; k < i; k++)
      {
         int jY = CloudArray[k].GetY();

         if((y - jY) < 30 && (y - jY) > 0)
         {
            y = rn.GenerateRandom(SKY_BOUND_1_Y+SPRITE_L_RR, SKY_BOUND_2_Y-SPRITE_L_RR);
            k = 0;
         }
      }

      CloudArray[i].SetX(x);
      CloudArray[i].SetY(y);
		CloudArray[i].Show(buffer);
		CloudArray[i].SetSpeed(-1);
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
bool PidgeRacer::MovePlayer(BITMAP *buffer)
{
   bool bLost = true;
   int pidge_no = 0;

	if(bMove && !bFinishLine)
	{
      //variable to loop screen once...
      static int loop_screen = 0;

      bg.EraseStartLine(buffer);

		for(int i = 0; i < NUMBER_OF_PIGEONS && !bFinishLine; i++)
		{
			if(pigeon_details[i].Pigeon.GetY() <= FINISH_LINE)   //increase race length, loop sky once...
			{
            if(loop_screen <= 0)
            {
               for(int j = 0; j < NUMBER_OF_PIGEONS; j++)
               {
                  pigeon_details[j].Pigeon.EraseOldSprite(buffer);
                  pigeon_details[j].Pigeon.SetY((INIT_POS_Y) + pigeon_details[j].Pigeon.GetY());
               }

               loop_screen++;
            }
            else   //handle completion of race...
            {
               //reset looping variable...
               loop_screen = 0;

   				bFinishLine = true;

               winner = pigeon_details[i].PidgeName;
               
               //code to increment number of races participated in and update
               //wins simultaneously... do at end so only increment once.
               score_values.update_stats(i);

               textprintf_ex(buffer, font, 710, 330, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
               textprintf_ex(buffer, font, 710, 330, makecol(255,0,0), makecol(0,0,0), "Winner: %s", winner.c_str());
   
               draw_sprite(buffer, flag, 60, 40);
               bg.DrawFinishLine(buffer);   

               for(int k = 0; k < NUMBER_OF_PIGEONS; k++)
               {
                  if(!pigeon_details[k].Pigeon.exploded)
                  {
                     if(pigeon_details[k].Pigeon.GetY() < INIT_POS_Y)
                     {
                        pigeon_details[k].Pigeon.Show(buffer,pigeon_details[k].Pigeon.GetX(),pigeon_details[k].Pigeon.GetY());
                     }
                  }
                  else
                  {
                     pigeon_details[k].Pigeon.exploded = false;   
                  }
               }

               string your_pigeon = "";

               //Calculate winnings...
               for(int j = 0; j < NUMBER_OF_PIGEONS; j++)
               {
                  if(pigeon_details[j].PigeonNumber == i && pigeon_details[j].selected == true)
                  {
                     winnings = (stake / pigeon_details[j].odds.second) * pigeon_details[j].odds.first;
                     wallet = wallet + winnings;   
                     bLost = false;
                  }

                  

                  if(pigeon_details[j].selected == true)
                  {
                     //a member variable is probably a good idea here, record on input...
                     pidge_no = j+1;
                     your_pigeon = pigeon_details[j].PidgeName;
                  }
   
               }
   
               string winnerloser = "is the WINNER!!!";
               string winlose = "won";
   
               if(bLost)
               {
                  winnings = stake;
                  wallet-=stake;
                  winnerloser = "has LOST...";
                  winlose = "lost"; 
               }


               if(wallet)     //greater than zero
               {
                  no_races++;

                  alfont_set_font_size(f, 20);   
      
                  alfont_textprintf_centre(buffer, f, 965, 482, makecol(0, 0, 0), "XXXXXXXXXXXXXXXXXXXXX", winlose.c_str(), winnings, wallet);
                  alfont_textprintf_centre(buffer, f, 965, 482, makecol(255, 255, 0), "Pigeon #%d: %s %s", pidge_no, your_pigeon.c_str(), winnerloser.c_str());
   
                  textprintf_ex(buffer, font, 710, 595, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXX");            
                  textprintf_ex(buffer, font, 710, 595, makecol(255,255,0), makecol(0,0,0), "You have %s $%d", winlose.c_str(), winnings);
                  textprintf_ex(buffer, font, 710, 615, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");            
                  textprintf_ex(buffer, font, 710, 615, makecol(255,255,0), makecol(0,0,0), "...Your new balance is $%d", wallet);

                  if(wallet > most_money)
                  {
                     most_money = wallet;
                  }

                  if(winnings > biggest_win)
                  {
                     biggest_win = winnings;
                  }
               }
               else
               {
                  no_races++;

                  bGameOver = true;
               }
            }
			}
			else   //Move Sprite...
			{

            //Delete original sprite...
            if(pigeon_details[i].Pigeon.GetY() <= INIT_POS_Y+10)
            {
               pigeon_details[i].Pigeon.EraseOldSprite(buffer);
            }
            
            //Call function to set new position of pigeon...
            pigeon_details[i].Pigeon.MoveOnY(buffer, screen);   

            //Draw new sprite in place of old on screen...
            if(pigeon_details[i].Pigeon.GetY() <= INIT_POS_Y+10)
            {        
               pigeon_details[i].Pigeon.DrawNewSprite(buffer, NULL);
            }

            //erase cloud, move to new position and redraw...
				for(int k = 0; k < NUMBER_OF_CLOUDS; k++)
				{
					CloudArray[k].MoveOnY(buffer, screen);
				}
			}

         //If we are on the second screen we can display the finishing line and handle the exploding pigeon...
         if(loop_screen > 0)
         {
            //draw finish line...
            if(pigeon_details[i].Pigeon.GetY() <= FINISH_LINE+150)
            {
               bg.DrawFinishLine(buffer);
            }
   
            //destroy pigeon! 
            if(pigeon_details[aim_vector.first].Pigeon.GetY() <= aim_vector.second)
            {
               pigeon_details[aim_vector.first].Pigeon.SetSpeed(0);
               pigeon_details[aim_vector.first].Pigeon.exploded = true;
               pigeon_details[aim_vector.first].Pigeon.EraseOldSprite(buffer);
               bb.DrawBang(buffer, pigeon_details[aim_vector.first].Pigeon.GetX(), aim_vector.second);
            }
         }

         //randomize pigeon speed variations...
         int speed_fluctuation = 0;
         int current_speed = pigeon_details[i].Pigeon.GetSpeed();

         switch(rn.GenerateBernoulli())
         {
            case 0:
            {
               speed_fluctuation = +1;
               if(current_speed <= 8)
               {
                  pigeon_details[i].Pigeon.SetSpeed(current_speed + speed_fluctuation); 
               }
               break;
            }

            case 1:
            {
               speed_fluctuation = -1;
               if(current_speed >= 2)
               {
                  pigeon_details[i].Pigeon.SetSpeed(current_speed + speed_fluctuation); 
               }
               break;
            }
         }

		}
	}	

   //IMPORTANT: ease up processor usage... 
   rest(15);

   return bGameOver;
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
void PidgeRacer::HandleReset(BITMAP *buffer)
{
   bMove = false;
   bFavorite = false;

   aim_vector = bb.ResetBang();

	bg.RedrawSky(buffer);

	SetupBackground(buffer);
	DrawClouds(buffer);
	DrawCharacters(buffer);
	bFinishLine = false;
   bg.EraseFinishLine(buffer);
	bg.DrawStartLine(buffer);

   DisplayBettingOdds(buffer);

   //TODO: move to more suitable function...
   textprintf_ex(buffer, font, 710, 330, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
   textprintf_ex(buffer, font, 710, 330, makecol(255,0,0), makecol(0,0,0), "Prev. winner: %s", winner.c_str());
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
void PidgeRacer::DisplayBettingTable(BITMAP* buffer)
{
   textout_ex(buffer, font, "Your Pigeons Today...               odds:          selection:", 710, 170, makecol(255, 0, 0), -1);
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
void PidgeRacer::DisplayRacingNames(BITMAP* buffer)
{
   //read scores from csv...
   score_values.ReadScores();      // could go in scores constructor?

   NameGenerator names;
   vector<string> name_list = names.NameList(NUMBER_OF_PIGEONS);

   char szPigeonName[100] = "";      
   for(int i = 0; i < name_list.size(); i++)
   {
      sprintf(szPigeonName, "Pigeon %d: ", i+1);
      textout_ex(buffer, font, szPigeonName, 710, (190+(15*i)), makecol(255, 0, 0), makecol(0, 0, 0));

      pigeon_details[i].PidgeName = name_list.at(i);
      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 790, (190+(15*i)), makecol(0, 0, 0), makecol(0, 0, 0));
      textout_ex(buffer, font, pigeon_details[i].PidgeName.c_str(), 790, (190+(15*i)), makecol(255, 0, 0), makecol(0, 0, 0));
     
      //code to enter pigeon details into stats table...
      bool nomatch = false;

      score_row no_match_stat;

      //compare to stats table... 
      for(int j = 0; j < score_values.row_count(); j++)
      {
         if(!pigeon_details[i].PidgeName.compare(score_values.read_row_data(j).name))
         {
            //matches
            score_values.make_active(i,j);
            nomatch = false;
            break;
         }
         else
         {
            //doesn't match, continue...
            nomatch = true;
         }
      }

      if(nomatch)
      {
         //TODO: constructor for the stat struct if possible...
         no_match_stat.name = pigeon_details[i].PidgeName;
         no_match_stat.index = i;
         no_match_stat.active = true;
         no_match_stat.races = 0;
         no_match_stat.wins = 0;
         no_match_stat.percent = 0;

         score_values.add_new(no_match_stat);
      }
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
void PidgeRacer::DisplayBettingOdds(BITMAP* buffer)
{
   OddsGenerator odds;
   pair<int, int> pigeon_odds[NUMBER_OF_PIGEONS];

   for (int i = 0; i < NUMBER_OF_PIGEONS; i++)
   {
      pigeon_details[i].odds = odds.GenerateOdds();
      
      //remove evens from results...
      bool bOK = false;
      while(!bOK)
      {
         if(pigeon_details[i].odds.first == pigeon_details[i].odds.second)
         {
            pigeon_details[i].odds = odds.GenerateOdds();
         }
         else
         {
            bOK = true;
         }
      }
   }

   for (int i = 0; i < NUMBER_OF_PIGEONS; i++)
   {
      textprintf_ex(buffer, font, 1000, (190+(15*i)), makecol(0, 0, 0), makecol(0, 0, 0), "XXXXXXXXXX", static_cast<int>(pigeon_details[i].odds.first), static_cast<int>(pigeon_details[i].odds.second));   
      textprintf_ex(buffer, font, 1000, (190+(15*i)), makecol(255, 0, 0), makecol(0, 0, 0), "%d/%d", static_cast<int>(pigeon_details[i].odds.first), static_cast<int>(pigeon_details[i].odds.second));   

      //int additional_speed = (static_cast<int>(pigeon_details[i].odds.first) % 6) + 1;
      //pigeon_details[i].Pigeon.SetSpeed( pigeon_details[i].Pigeon.GetSpeed() + additional_speed );
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
void PidgeRacer::DisplayCheckBoxes(BITMAP *buffer)
{
   textout_ex(buffer, font, "Selected: ", 710, 310, makecol(255,0,0), makecol(0,0,0));

   int bg_ok = 0;
   int fg_ok = 0;
 
   if(bSelectionComplete)
   {
      bg_ok = makecol(255,255,0);
      fg_ok = makecol(100,100,100);
   }
   else
   {
      bg_ok = makecol(255,0,0);
      fg_ok = makecol(0,0,0);
   }

   for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
   {
      if((mouse_x >= 1153 && mouse_x <= 1161) && (mouse_y >= 193+(15*i) && mouse_y <= 201+(15*i)))
      {
         if(!bSelectionComplete)
         {
            rectfill(buffer, 1153, 193+(15*i), 1161, 201+(15*i), makecol(255,0,0));

            if(mouse_b & 1)
            {
               for(int j = 0; j < NUMBER_OF_PIGEONS; j++)
               {
                  if(j != i)
                  {
                     pigeon_details[j].selected = false;
                  }
                  else
                  {
                     pigeon_details[i].selected = true;
                     bPigeonSelected = true;
                  }
               }
            }

            textprintf_ex(buffer, font, 790, 310, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
            textprintf_ex(buffer, font, 790, 310, makecol(255,0,0), makecol(0,0,0), "%s", pigeon_details[i].PidgeName.c_str());
         }
      }
      else
      {
         if(pigeon_details[i].selected == true)
         {
            rectfill(buffer, 1153, 193+(15*i), 1161, 201+(15*i), bg_ok);
         }
         else
         {
            rectfill(buffer, 1153, 193+(15*i), 1161, 201+(15*i), makecol(0,0,0));
            rect(buffer, 1153, 193+(15*i), 1161, 201+(15*i), makecol(255,0,0));
            rect(buffer, 1154, 194+(15*i), 1160, 200+(15*i), makecol(190,0,0));
         }
      }
   }

   rectfill(buffer, 990, 310, 1190, 340, bg_ok);

   textout_ex(buffer, font, "XXXXXXXXXXXXXX", 1038, 322, bg_ok, bg_ok);

   if((mouse_x >= 990 && mouse_x <= 1190) && (mouse_y >= 310 && mouse_y <= 340))
   {
      rectfill(buffer, 990, 310, 1190, 340, bg_ok);
      textout_ex(buffer, font, "Make your Bet", 1038, 322, makecol(100, 100, 100), bg_ok);

      if(mouse_b & 1)
      {
         if(!bPigeonSelected)
         {
            textprintf_ex(buffer, font, 710, 290, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
            textprintf_ex(buffer, font, 710, 290, makecol(255,0,0), makecol(0,0,0), "WARNING: CHOOSE YOUR PIGEON PLEASE...");
         }
         else
         {
            textprintf_ex(buffer, font, 710, 290, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
            bSelectionComplete = true;
            text.EnableInput();

            if(!bFavorite)
            {
               for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
               {
                  if(pigeon_details[i].selected)
                  {
                     pigeon_details[i].count++;
                  }
               }
               
               bFavorite = true;
            }
         }
      }
   }
   else
   {
      textout_ex(buffer, font, "Make your Bet", 1038, 322, fg_ok, bg_ok);
   }

   //keep mouse on top of CheckBoxes...
   show_mouse(buffer);
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
void PidgeRacer::DisplayBettingForm(BITMAP *buffer)
{
   int bg_ok = 0;
   int fg_ok = 0;
 
   if(bBettingComplete)
   {
      bg_ok = makecol(255,255,0);
      fg_ok = makecol(100,100,100);
   }
   else
   {
      bg_ok = makecol(255,0,0);
      fg_ok = makecol(0,0,0);
   }

   int fg_stake = 0;
   if(bSelectionComplete)
   {
      fg_stake = makecol(100,100,100);
   }
   else
   {
      fg_stake = makecol(0,0,0);
   }

	line(buffer, 710, 370, 1200, 370, makecol(255, 255, 255));

   //display amount of money user has
   textprintf_ex(buffer, font, 710, 400, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
   textprintf_ex(buffer, font, 710, 400, makecol(255,0,0), makecol(0,0,0), "You have: $ %d", wallet);

   if(bSelectionComplete && !bBettingComplete)
   {
      //highlight the input field...
      textout_ex(buffer, font, "Bet:", 710, 415, makecol(255, 255, 0), makecol(0, 0, 0));
      textout_ex(buffer, font, "$", 750, 415, makecol(255, 255, 0), makecol(0, 0, 0));
   }
   else if(!bSelectionComplete || bBettingComplete)
   {
      textout_ex(buffer, font, "Bet:", 710, 415, makecol(255, 0, 0), makecol(0, 0, 0));
      textout_ex(buffer, font, "$", 750, 415, makecol(255, 0, 0), makecol(0, 0, 0));
   }

   //place input field on form for text input...
   text.InputField(buffer, 20, 765, 415, makecol(255,255,0), makecol(0,0,0));

   rectfill(buffer, 990, 395, 1190, 425, bg_ok);

   if((mouse_x >= 990 && mouse_x <= 1190) && (mouse_y >= 395 && mouse_y <= 425))
   {

      rectfill(buffer, 990, 395, 1190, 425, bg_ok);
      textout_ex(buffer, font, "OK", 1080, 407, fg_stake, bg_ok);

      if(bSelectionComplete)
      {   
         if(mouse_b & 1)
         {
            stake = atoi(text.OutputValue().c_str());
            if(stake)
            {
               textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 710, 440, makecol(0,0,0), makecol(0,0,0));

               if(stake > wallet)
               {
                  textout_ex(buffer, font, "WARNING: You do not have that much money!", 710, 440, makecol(255,0,0), makecol(0,0,0));
               }
               else if(stake <= 0)
               {
                  textout_ex(buffer, font, "WARNING: Please enter a value greater than zero,", 710, 440, makecol(255,0,0), makecol(0,0,0));
               }
               else
               {
                  text.DisableInput();
                  text.SetText(buffer, makecol(255,0,0), makecol(0,0,0));
                  bBettingComplete = true;
               }
            }
         }
      }
   }
   else
   {
      textout_ex(buffer, font, "OK", 1080, 407, fg_ok, bg_ok);
   }

   //keep mouse on top of Buttons...
   show_mouse(buffer);
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
void PidgeRacer::DisplayStartRace(BITMAP *buffer)
{
   int fg_ok = 0;
   if(bBettingComplete)
   {
      fg_ok = makecol(255,255,0);
   }
   else
   {
      fg_ok = makecol(0,0,0);
   }

	line(buffer, 710, 465, 1200, 465, makecol(255, 255, 255));

   rectfill(buffer, 830, 520, 1100, 560, makecol(255, 0, 0));
   textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXX", 920, 537, makecol(255, 0, 0), makecol(255, 0, 0));

   if((mouse_x >= 830 && mouse_x <= 1100) && (mouse_y >= 520 && mouse_y <= 560))
   {
      if(!bFinishLine)
      {
         textout_ex(buffer, font, "START RACE!", 920, 537, fg_ok, makecol(255, 0, 0));
      }
      else
      {
         textout_ex(buffer, font, "NEW RACE!", 930, 537, makecol(0, 0, 0), makecol(255, 0, 0));
      }

      if(bBettingComplete)
      {
         if(mouse_b & 1)
         {
            bMove = true;
         }
      }

      if(bFinishLine)
      {
         //if(wallet)
         {
            textout_ex(buffer, font, "NEW RACE!", 930, 537, makecol(255, 255, 0), makecol(255, 0, 0));
   
            if(mouse_b & 1)
            {
               bMove = false;
               bSelectionComplete = false;
               bBettingComplete = false;
               HandleReset(buffer);
            }
         }
         //else
         //{
         //   if(mouse_b & 1)
         //   {
         //      rectfill(buffer, 100, 100, 900, 900, makecol(0,255,0));

               //draw GAME OVER! segment...
               //bMove = false;
               //bSelectionComplete = false;
               //bBettingComplete = false;
               //HandleReset(buffer);
          //  }
         //}
      }
   }
   else
   {
      if(!bFinishLine)
      {
         textout_ex(buffer, font, "START RACE!", 920, 537, makecol(0, 0, 0), makecol(255, 0, 0));
      }
      else
      {
         textout_ex(buffer, font, "NEW RACE!", 930, 537, makecol(0, 0, 0), makecol(255, 0, 0));
      }
   }   


   //simple speed output routine to check random number generation...
   /*for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
   {
      textprintf_ex(buffer, font, INIT_POS_X+(20*(i*2)), INIT_POS_Y+120, makecol(0,0,0), makecol(0,0,0), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
      textprintf_ex(buffer, font, INIT_POS_X+(20*(i*2)), INIT_POS_Y+120, makecol(255,0,0), makecol(0,0,0), "%d", pigeon_details[i].Pigeon.GetSpeed());
   }*/
   

   //keep mouse on top of Buttons...
   show_mouse(buffer);
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
void PidgeRacer::TitleAndTagline(BITMAP *buffer)
{
   if(!bMove)
   {
      alfont_set_font_size(f, 20);   
   
      alfont_textout_centre(buffer, f, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 965, 482, makecol(0,0,0));
      alfont_textout_centre(buffer, f, ":: Pidgeracer Revolution ::", 965, 482, makecol(100,100,100));

      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXX",710, 595, makecol(0,0,0), makecol(0,0,0));            
      textout_ex(buffer, font, "Your bet, your future", 710, 595, makecol(255,0,0), makecol(0,0,0));
      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 710, 615, makecol(0,0,0), makecol(0,0,0));            
      textout_ex(buffer, font, "...think about it.", 710, 615, makecol(255,0,0), makecol(0,0,0));
   }

   show_mouse(buffer);
}

void draw_pattern(BITMAP *bitmap, char *message, int color)
{
   BITMAP *pattern;
   acquire_bitmap(bitmap);

   /* destroy the pattern bitmap */
   destroy_bitmap(pattern);

   release_bitmap(bitmap);
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
void PidgeRacer::HallOfFame(BITMAP *buffer)
{
   textout_ex(buffer, font, "Name                    Wins    %", 715, 685, makecol(255, 255, 255), makecol(0, 0, 0));

	line(buffer, 710, 695, 980, 695, makecol(255, 255, 255));
	line(buffer, 710, 901, 900, 901, makecol(255, 255, 255));
	line(buffer, 710, 680, 980, 680, makecol(255, 255, 255));

   if(bHallOfFame)
   {
      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXX", 715, 660, makecol(0, 0, 0), makecol(0, 0, 0));
      textout_ex(buffer, font, "Pidgeracer: Hall of Fame", 715, 660, makecol(255, 255, 255), -1);
      textout_ex(buffer, font, "Current", 715, 912, makecol(255, 0, 0), -1);
      textout_ex(buffer, font, "Hall of Fame", 795, 912, makecol(255, 255, 0), -1);
   }
   else
   {
      textout_ex(buffer, font, "XXXXXXXXXXXXXXXXXXXXXXXXXXX", 715, 660, makecol(0, 0, 0), makecol(0, 0, 0));
      textout_ex(buffer, font, "Pidgeracer: Current Racers", 715, 660, makecol(255, 255, 255), -1);
      textout_ex(buffer, font, "Current", 715, 912, makecol(255, 255, 0), -1);
      textout_ex(buffer, font, "Hall of Fame", 795, 912, makecol(255, 0, 0), -1);
   }

   textout_ex(buffer, font, " | ", 770, 912, makecol(255, 255, 255), makecol(0, 0, 0));

   if((mouse_x >= 715 && mouse_x <= 768) && (mouse_y >= 912 && mouse_y <= 922))
   {
      if(mouse_b & 1)
      {
         bHallOfFame = false;
      }
   }

   if((mouse_x >= 795 && mouse_x <= 890) && (mouse_y >= 912 && mouse_y <= 922))
   {
      if(mouse_b & 1)
      {
         bHallOfFame = true;
      }
   }

   // Hall of fame ordering below...
   int count = score_values.row_count();
  
   draw_sprite(buffer, score_board, 712, 701);

   int x = 0;

   if(bHallOfFame)
   {
      for(x = 0; x < count && x < MAX_SCOREBOARD; x++)
      {
         score_row row = score_values.read_row_data(x);
   
         //real ugly code below... change at some point...
         stringstream string_out;
         string_out << row.name;
     
         textout_ex(buffer, font, string_out.str().c_str(), 715, 705+(15*x), makecol(255, 255, 255), -1);
   
         string_out.str("");
         string_out << row.wins;
    
         textout_ex(buffer, font, string_out.str().c_str(), 920, 705+(15*x), makecol(255, 255, 255), -1);
   
         string_out.str("");
         //string_out << static_cast<short>(row.percent);
         string_out << setprecision(3) << row.percent;
   
         textout_ex(buffer, font, string_out.str().c_str(), 970, 705+(15*x), makecol(255, 255, 255), -1);
      }
   }
   else
   {
      //Only display active racers, "current racers".
      //TODO: As vector size grows, might need to implement a better search algorithm...
      //TODO: As around 900k gets stored here we know we need to implement a better search algorithm! 

      int y = 0;

      do
      {
         score_row row = score_values.read_row_data(y);
      
         if(row.active)
         {
            stringstream string_out;
            string_out << row.name;
        
            textout_ex(buffer, font, string_out.str().c_str(), 715, 705+(15*x), makecol(255, 255, 255), -1);

            string_out.str("");
            string_out << row.wins;
       
            textout_ex(buffer, font, string_out.str().c_str(), 920, 705+(15*x), makecol(255, 255, 255), -1);
      
            string_out.str("");
            //string_out << static_cast<short>(row.percent);
            string_out << setprecision(3) << row.percent;
      
            textout_ex(buffer, font, string_out.str().c_str(), 970, 705+(15*x), makecol(255, 255, 255), -1);

            x++;
            y++;
         }
         else
         {
            y++;
         }  
      }
      while(x < NUMBER_OF_PIGEONS);
   }

   show_mouse(buffer);
}

/***********************************************************************
*
*  Name:    another_gameover_handler()
*
*  Author:  Ross Spencer
*
*  Purpose: 
*
**********************************************************************/
void PidgeRacer::AnotherGameOverHandler(BITMAP *buffer, BITMAP *exit_b1, BITMAP *exit_b2, BITMAP *restart_b1, BITMAP *restart_b2)
{
   rectfill(buffer, 50, 950, 100, 1000, makecol(0,0,0));

   textout_ex(buffer, font, "Exit", 255, 675, makecol(255,0,0), -1);

   if((mouse_x >= 250 && mouse_x <= 290) && (mouse_y >= 640 && mouse_y <= 690))
   {
      draw_sprite(buffer, exit_b2, 250, 640);
      
      if(mouse_b & 1)
      {
         key[KEY_ESC] = true;
      }
   }
   else
   {
      draw_sprite(buffer, exit_b1, 250, 640);       
   }

   show_mouse(buffer);

   textprintf_ex(buffer, font, 358, 477, makecol(0,255,0), -1, "$ %d", most_money);
   textprintf_ex(buffer, font, 366, 494, makecol(0,255,0), -1, "$ %d", biggest_win);

   std::pair <int,int>count;
   count.first = 0;
   count.second = pigeon_details[0].count;

   for(int i = 0; i < NUMBER_OF_PIGEONS; i++)
   {

      //textprintf_ex(buffer, font, 380, 560+(i*10), makecol(0,255,0), -1, "%d", pigeon_details[i].count);


      if(pigeon_details[i].count > count.second)
      {
         count.first = i;
         count.second = pigeon_details[i].count;
      }


   }

   textprintf_ex(buffer, font, 400, 510, makecol(0,255,0), -1, "%s", pigeon_details[count.first].PidgeName.c_str());
   textprintf_ex(buffer, font, 400, 528, makecol(0,255,0), -1, "%d", no_races);
   textprintf_ex(buffer, font, 370, 544, makecol(0,255,0), -1, "%d", no_races*10);

   //TODO: Handle a reset here...
   //textout_ex(buffer, font, "New Game", 298, 675, makecol(0,255,0), -1);
   /*if((mouse_x >= 308 && mouse_x <= 348) && (mouse_y >= 640 && mouse_y <= 690))
   {
      draw_sprite(buffer, restart_b2, 308, 640);
      
      if(mouse_b & 1)
      {
         //bReset = true;
      }
   }
   else
   {
      draw_sprite(buffer, restart_b1, 308, 640);       
   }*/

   //return bReset;
}
