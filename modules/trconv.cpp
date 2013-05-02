//# -*- coding: cp1251 -*-
#include "samp.h"

//#include <cstdio>

// rescued from lsfr

static const char en_ru_transform[][2] =
{
    /*
    { '\xE9', 'q' },
    { '\xF6', 'w' },
    { '\xF3', 'e' },
    { '\xEA', 'r' },
    { '\xE5', 't' },
    { '\xED', 'y' },
    { '\xE3', 'u' },
    { '\xF8', 'i' },
    { '\xF9', 'o' },
    { '\xE7', 'p' },
    { '\xF4', 'a' },
    { '\xFB', 's' },
    { '\xE2', 'd' },
    { '\xE0', 'f' },
    { '\xEF', 'g' },
    { '\xF0', 'h' },
    { '\xEE', 'j' },
    { '\xEB', 'k' },
    { '\xE4', 'l' },
    { '\xFF', 'z' },
    { '\xF7', 'x' },
    { '\xF1', 'c' },
    { '\xEC', 'v' },
    { '\xE8', 'b' },
    { '\xF2', 'n' },
    { '\xFC', 'm' },
    */
    { '\xB8', '`' },
    { '?', ',' },
    { '/', '.' },
    { '\xF5', '[' },
    { '\xFA', ']' },
    { '\xE6', ';' },
    { '\xFD', '\''},

    { '.', '/' },
    { '\"','@' },
    { '?', '&' },
    { ',', '?' },
    //{ '\xB9', '#' },
    { '$', ';' },
    { ':', '^' }
};



static const char en_ru_tralphabet[] = "\xF4\xE8\xF1\xE2\xF3\xE0\xEF\xF0\xF8\xEE\xEB\xE4\xFC\xF2\xF9\xE7\xE9\xEA\xFB\xE5\xE3\xEC\xF6\xF7\xED\xFF"; // abcdefghijkl....
static const char ru_en_tralphabet[] = "f,dult;pbqrkvyjghcnea[wxio]sm\'.z";

#define isupper_lat(ch) (((ch)>='A')&&((ch)<='Z'))
#define islower_lat(ch) (((ch)>='a')&&((ch)<='z'))

#define toupper_lat(ch) (islower_lat(ch)?((ch)-'a'+'A'):(ch))
#define tolower_lat(ch) (isupper_lat(ch)?((ch)-'A'+'a'):(ch))

#define isupper_cyr(ch) (((ch)>='\xC0')&&((ch)<='\xDF'))
#define islower_cyr(ch) (((ch)>='\xE0')&&((ch)<='\xFF'))

#define toupper_cyr(ch) (islower_cyr(ch)?((ch)-'\xE0'+'\xC0'):(ch))
#define tolower_cyr(ch) (isupper_cyr(ch)?((ch)-'\xC0'+'\xE0'):(ch))

#define isupper(ch) (isupper_lat(ch)||isupper_cyr(ch))
#define islower(ch) (islower_lat(ch)||islower_cyr(ch))

#define toupper(ch) (islower_lat(ch)?toupper_lat(ch):toupper_cyr(ch))
#define tolower(ch) (isupper_lat(ch)?tolower_lat(ch):tolower_cyr(ch))

#define isletter_cyr(ch) (isupper_cyr(ch)||islower_cyr(ch))
#define isletter_lat(ch) (isupper_lat(ch)||islower_lat(ch))


#define isletter(ch) (isletter_lat(ch)||isletter_cyr(ch))
#define isdigit(ch) (((ch)>='0')&&((ch)<='9'))
#define isspacer(ch) ((ch)==' '||(ch)=='\t'||(ch)=='\r'||(ch)=='\n')


static void on_player_text(int /**/, std::string& text)
{
  int len = text.size();
  //printf("%d\n", len);
  if(len>3 && ((text[len-1]=='$' && text[len-2] == '^') ||
    (text[len-2]== ':' && text[len-1] == ';' && isletter_cyr(text[len-3]))))
  {
    len -= 2; // ^$
    for(int i = 0, tr = 2; i < len; i++)
    {
      int tmp = text[i]; // save
      //printf("%c %d\n", tmp, tmp);
      if(islower_lat(tmp))
      {
        tmp -= 'a';
        tr = 0; // eng
      }
      else if(isupper_lat(tmp))
      {
        tmp -= 'A';
        tr = 1; // ENG
      }
      else if(islower_cyr(tmp))
      {
        tmp -= '\xE0';
        tr = 2; // rus
      }
      else if(isupper_cyr(tmp))
      {
        tmp -= '\xC0';
        tr = 3; // RUS
      }
      else // non-alpha
      {
        for(unsigned int j=0; j<sizeof(en_ru_transform); j++)
        {
          if((tr == 2 || tr == 3) && text[i] == en_ru_transform[j][0])
          {
            text[i] = en_ru_transform[j][1];
            break;
          }
          else if(text[i] == en_ru_transform[j][1])
          {
            text[i] = tmp = en_ru_transform[j][0];
            if(tr == 1)
                text[i] = tmp != '\xB8' ? toupper_cyr(tmp) : '\xA8';
            else if(tr == 3)
                text[i] = toupper_lat(tmp);
            break;
          }
        }
        continue;
      }

      if(tr == 0 || tr == 1)
        text[i] = en_ru_tralphabet[tmp];
      else if(tr == 2 || tr == 3)
        text[i] = ru_en_tralphabet[tmp];

      if(tr == 1)
        text[i] = text[i] - 'a' + 'A';
      else if(tr == 3)
        text[i] = text[i] - '\xE0' + '\xC0';
      //printf("- %d %c\n", tr, text[i]);
    }
    text.erase(len);
    //return true;
  }
  //printf("%s\n", text.c_str());
}


INIT
{
  REGISTER_CALLBACK(on_player_text, -100000, &on_player_text); // first
}
