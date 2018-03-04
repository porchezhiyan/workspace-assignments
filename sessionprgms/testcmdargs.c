#include "stdio.h"
int main(int argc,char** argb)
{
	printf("%d \n %s \n %s \n",argc,*argb,*(argb+1));
	return argc; 
}
