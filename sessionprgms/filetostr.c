#include"stdio.h"
#include"utils.h"
#include"stdlib.h"
void main()
{
	char* string;
	string =(char*)malloc(25);
	FILE*fp = fopen("textfile.txt","rb");
	fread(string,25,1,fp);
	printf("%s",string);
}
