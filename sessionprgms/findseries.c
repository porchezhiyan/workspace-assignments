#include"stdio.h"
void main()
{
	printf("\n \n ----------------------------------------Program to print the result of an arithmetic of series of 1 + 1/2 + ...+1/n  ---------------------------------------------------\n");
	printf("\n\n\n");
	int ch = 1;
while(ch==1)
{
	printf("please enter the value of \'n\' \n");

	int n;
	scanf("%d",&n);
	int n1 = 1;
	int d1 = 1;
	int n2 = 1;
	int d2 = 2;
	while(d2<=n)
	{
		n1 =( n1*d2 + n2 * d1);
		d1 = d1*d2;
		n2 = 1;
		d2 = d2+1;
	}
	printf("the sum of the series is : %d/%d\n\n",n1,d1);
	int t1 = n1,t2 = d1,f = 0;
	if(t1<t2)
	{
		t1 = t1+t2;
		t2 = t1-t2;
		t1 = t1-t2;
		f=1;


	}
	for(;t2>=1;t2--)
	{
		if(t1%t2==0&&d1%t2==0)
		{
			break;
		}
	}
//	if(f==0)
        	printf("the common factor is  : %d\n\n",t2);
//        
        printf("the simplified result is : %d/%d\n\n",(n1/t2),(d1/t2));

	
	printf("to continue press \'1\' \n to exit press any key \n");
	scanf("%d",&ch);
}

}
