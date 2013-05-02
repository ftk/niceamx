#include <stdio.h>


int main()
{
	
	FILE * fp_in = fopen("test.txt", "r");
	FILE * fp_out = fopen("out.txt", "w");
	
	
	int ch = fgetc(fp_in);
	while(ch != EOF)
	{
		if(ch < 128)
		{
			fputc(ch, fp_out);
		}
		else
		{
			char buf[64];
			snprintf(buf, sizeof(buf), "\\x%02X", ch);
			fputs(buf, fp_out);
		}
		ch = fgetc(fp_in);
	}
	
	return 0;
}


