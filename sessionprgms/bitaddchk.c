#include"stdio.h"
int carry = 0;
int binsum(int bin1,int bin2)
{
	if(bin1&&bin2)			//case of 1 1
	{	printf("both 1\n");
		if(!carry)
		{
			carry = 1;
			return 0;
		}
		else
		{
			carry = 1;
			return 1;
		}
	}
	if(bin1||bin2)
        {
		printf("either 1");

                if(!carry)
                {
                        carry = 0;
                        return 1;
                }
                else
                {
                        carry = 1;
                        return 0;
                }
        }
	else
        {
		printf("both 0");

                if(!carry)
                {
                        carry = 0;
                        return 0;
                }
                else
                {
                        carry = 0;
                        return 1;
                }
        }
	
}
void main()
{
	int b1 , b2 ;
	scanf("%d %d",&b1,&b2);
	printf("res : %d \n carry :  %d \n ",binsum(b1,b2),carry);
	printf("final carry: %d \n",carry);	
}

