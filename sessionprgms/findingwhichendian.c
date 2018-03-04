#include"stdio.h"
//#include"conio.h"
void main(){
	char start;
	printf("Program to find whether this System follows big endian or little endian method of address allocation for its bytes \n");
	printf("press \'enter\' to find \n");
	scanf("%c",&start);

	unsigned int ivar = 0x12345678;	//assigning arbitrarily 
	
	char *c=(char*)&ivar;	//assigns the starting address of ivar to a character pointer
	if(*c==78)	//checks whether bits of ivar  starts with least signficant byte
		printf("this system follows LittleEndian memory representation \n"); //if condition is true  system is LE
	else
		printf("this system follows BigEndian memory representation \n"); // if condition is false system is BE
}
