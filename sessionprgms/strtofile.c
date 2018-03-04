#include"stdio.h"
#include"utils.h"
#include"stdlib.h"
void main()
{
	char* string;
	string =(char*)malloc(25);
	str_cpy(string,"HELLOWORLD");
	FILE*fp = fopen("textfile.txt","wb");
	fwrite(string,25,1,fp);
}
