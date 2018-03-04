#include"stdio.h"
void main()
{
	printf("\n \n ----------------------------------------Program to print the result of an arithmetic of series of 1 + 1/2 + ...+1/n  ---------------------------------------------------\n");
	printf("\n\n\n");
	int ch = 1;
while(ch==1)
{
	printf("\tplease enter the value of \'n\' \n");

	int n;
	if(scanf("%d",&n)==0){
		printf("\tplease enter a positive integer\n");
		while(getchar()!='\n')
			;
		continue;
	}
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
	printf("\tthe sum of the series is : %d/%d\n\n",n1,d1);
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
        	printf("\tthe common factor is  : %d\n\n",t2);
//        
        printf("\tthe simplified result is : %d/%d\n\n",(n1/t2),(d1/t2));

	
	printf("\tto continue press \'1\' \n\t to exit press any key \n");
	if(scanf("%d",&ch)==0)
		break;
	
}

}
