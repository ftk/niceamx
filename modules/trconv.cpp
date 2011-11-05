#include "samp.h"

#include <cstdio>

static const char en_ru_transform[][2] =
{
	/*
	{ 'é', 'q' },
	{ 'ö', 'w' },
	{ 'ó', 'e' },
	{ 'ê', 'r' },
	{ 'å', 't' },
	{ 'í', 'y' },
	{ 'ã', 'u' },
	{ 'ø', 'i' },
	{ 'ù', 'o' },
	{ 'ç', 'p' },
	{ 'ô', 'a' },
	{ 'û', 's' },
	{ 'â', 'd' },
	{ 'à', 'f' },
	{ 'ï', 'g' },
	{ 'ð', 'h' },
	{ 'î', 'j' },
	{ 'ë', 'k' },
	{ 'ä', 'l' },
	{ 'ÿ', 'z' },
	{ '÷', 'x' },
	{ 'ñ', 'c' },
	{ 'ì', 'v' },
	{ 'è', 'b' },
	{ 'ò', 'n' },
	{ 'ü', 'm' },
	*/
	{ '¸', '`' },
        { '?', ',' },
        { '/', '.' },
	{ 'õ', '[' },
	{ 'ú', ']' },
	{ 'æ', ';' },
	{ 'ý', '\''},

	{ '.', '/' },
	{ '\"','@' },
	{ '?', '&' },
	{ ',', '?' },
	//{ '¹', '#' },
	{ '$', ';' },
	{ ':', '^' }
};



static const char en_ru_tralphabet[] = "ôèñâóàïðøîëäüòùçéêûåãìö÷íÿ"; // abcdefghijkl....
static const char ru_en_tralphabet[] = "f,dult;pbqrkvyjghcnea[wxio]sm\'.z"; // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½...

#define isupper_lat(ch) (((ch)>='A')&&((ch)<='Z'))
#define islower_lat(ch) (((ch)>='a')&&((ch)<='z'))

#define toupper_lat(ch) (islower_lat(ch)?((ch)-'a'+'A'):(ch))
#define tolower_lat(ch) (isupper_lat(ch)?((ch)-'A'+'a'):(ch))

#define isupper_cyr(ch) (((ch)>='À')&&((ch)<='ß'))
#define islower_cyr(ch) (((ch)>='à')&&((ch)<='ÿ'))

#define toupper_cyr(ch) (islower_cyr(ch)?((ch)-'à'+'À'):(ch))
#define tolower_cyr(ch) (isupper_cyr(ch)?((ch)-'À'+'à'):(ch))

#define isupper(ch) (isupper_lat(ch)||isupper_cyr(ch))
#define islower(ch) (islower_lat(ch)||islower_cyr(ch))

#define toupper(ch) (islower_lat(ch)?toupper_lat(ch):toupper_cyr(ch))
#define tolower(ch) (isupper_lat(ch)?tolower_lat(ch):tolower_cyr(ch))

#define isletter_cyr(ch) (isupper_cyr(ch)||islower_cyr(ch))
#define isletter_lat(ch) (isupper_lat(ch)||islower_lat(ch))


#define isletter(ch) (isletter_lat(ch)||isletter_cyr(ch))
#define isdigit(ch) (((ch)>='0')&&((ch)<='9'))
#define isspacer(ch) ((ch)==' '||(ch)=='\t'||(ch)=='\r'||(ch)=='\n')


static void on_player_text(int playerid, std::string& text)
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
	tmp -= 'à';
	tr = 2; // rus
      }
      else if(isupper_cyr(tmp))
      {
	tmp -= 'À';
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
		    text[i] = tmp != '¸' ? toupper_cyr(tmp) : '¨';
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
	text[i] = text[i] - 'à' + 'À';
      //printf("- %d %c\n", tr, text[i]);
    }
    text.erase(len);
    //return true;
  }
  //printf("%s\n", text.c_str());
}


INIT
{
  REGISTER_CB(on_player_text);
}
