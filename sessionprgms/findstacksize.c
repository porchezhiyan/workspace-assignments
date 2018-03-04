#include"stdio.h"
#include"stdlib.h"
int i = 0;
void main()
{
	int * ptr ;
	ptr = (int*)malloc(i*1000);

	 int a = 5;
	int *p = &a;
	int b =(unsigned long int) p;
	printf("\n %d %d \n",i,b);
	i+=48;
	main();

}

