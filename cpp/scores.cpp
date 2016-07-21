#include "scores.h"

/**********************************************************************
*
*  Name:       
*
*  Author:     
*
*  Purpose:    
*
**********************************************************************/
Scores::Scores()
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
Scores::~Scores()
{
   fstream new_file("scores.csv", std::ios_base::out | std::ios_base::binary);

   score_row *temp_row;

   if(new_file.is_open())
   {
      for(int i = 0; i < score_rows.size(); i++)
      {
         temp_row = &score_rows.at(i);
         new_file << temp_row->name << "," << temp_row->wins << "," << temp_row->races << endl;
      }
   }

   new_file.close();
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
void Scores::make_active(short pidge_index, int stat_index)
{
   score_rows.at(stat_index).index = pidge_index;
   score_rows.at(stat_index).active = true;
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
void Scores::add_new(score_row row_data)
{
   score_rows.push_back(row_data);
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
void Scores::update_stats(short pidge_index)
{
   score_row *temp_row;

   for(int i = 0; i < score_rows.size(); i++)
   {
      temp_row = &score_rows.at(i);
      if(temp_row->active)
      {
         temp_row->races++;

         if(temp_row->index == pidge_index)
         {
            temp_row->wins++;
         }

         temp_row->percent = (temp_row->wins / temp_row->races) * 100;
      }
   }

   scores_sort();
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
score_row Scores::read_row_data(int pos)
{
   return score_rows.at(pos);
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
bool Scores::ReadScores()
{
   fstream score_file;
   score_file.open("scores.csv", fstream::in);


   if(score_file.is_open())
   {
      score_row row;
      string line;
   
      int count = 0;
   
      while(getline (score_file, line))
      {
         istringstream linestream(line);
         string item;
         getline (linestream, item, ',');
         row.name = item;
         getline (linestream, item, ',');
   
         //NOTE: Getting to the depths of really crap code below, must fix at some point...
         //NOTE: Although, at least this currently works.
         //TODO: should probably be taken out of the loop (w/ time)
         stringstream test(item);
         test >> row.wins;
         getline (linestream, item, ',');
         //TODO: should probably be taken out of the loop (w/ time)
         stringstream test2(item);
         test2.str(item);
         test2 >> row.races;     
   
         row.active = false;
         row.percent = 0;
   
         score_rows.push_back(row);
      }
   
      score_file.close();

   }
   else
   {
      score_row row("Samurai Roadrunner",0,0);
      score_rows.push_back(row);
      row.name = "Cowabunga Guard";
      score_rows.push_back(row);
      row.name = "Mafia Jazz";
      score_rows.push_back(row);
      row.name = "Usagi Yojimbo";
      score_rows.push_back(row);
      row.name = "Tank Girl";
      score_rows.push_back(row);
      row.name = "Yamaha Mustang";
      score_rows.push_back(row);
      row.name = "Die Hard 4.0";
      score_rows.push_back(row);
      row.name = "Samurai Dynamite";
      score_rows.push_back(row);
      row.name = "Mustang Buzz";
      score_rows.push_back(row);
      row.name = "Cobra Girl";
      score_rows.push_back(row);
      row.name = "Blitzkrieg Blitz";
      score_rows.push_back(row);
      row.name = "Hitman Hart";
      score_rows.push_back(row);
   }

   score_row *temp_row;

   for(int i = 0; i < score_rows.size(); i++)
   {
      temp_row = &score_rows.at(i);
      if(!temp_row->wins)
      {
         temp_row->percent = 0;
      }
      else
      {
         temp_row->percent = (temp_row->wins / temp_row->races) * 100; 
      }
   }

   scores_sort();

   return 0;
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
bool Scores::WriteScores()
{
   //to be run almost at absolute end of game. (see cleanup() - should probs be first function call in there...)
   //nothing special to do, simply truncate file and output score_rows vector line by line
   //format for csv. should do the trick nicely. 



/*
   xml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>";
   xml << "<files>";
   xml_out.open("files\\list.xml", std::ios_base::out);
*/

/*
   fstream new_file("scores.xml", std::ios_base::out | std::ios_base::binary);

   if(new_file.is_open())
   {
         new_file << "this is a test" << std::endl;
   }
*/  


/*
   else
   {
         fstream new_file("pidge_error.txt", std::ios_base::out | std::ios_base::binary);

         new_file << "already exists...";
   }
*/


   return true;
}
