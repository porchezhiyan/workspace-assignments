#include"stdio.h"
#include"stdlib.h"
#define A 100
void main()
{
	{
		# undef A
		# define A 200
		        printf("%d",A); 

	}

	printf("%s %s %s %d ",__TIME__,__DATE__,__FILE__,__LINE__);	
}
