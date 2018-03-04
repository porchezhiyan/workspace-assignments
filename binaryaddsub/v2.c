/*PROGRAM TO GET TWO INPUTS FROM USER AND ADD OR SUBTRACT THEM IN USING BINARY OPERATION*/
#include"stdio.h"
#include"stdlib.h"
int carry = 0;	//create a variable to hold carry globally and initialise it to 0
int overflow =0;
int negateinteger(int bin)
{
	for(int i = 0 ; i <= 31 ; i++)
	{
		bin = bin ^ (1<<i);
	}
	return bin;	
}
void chartobin(int n){
	void displaybin(int c)
	{
		// printf("%d",c);
		printf("\n \t");
		for(int i = 31 ; i >= 0 ; i--){
			if((c) &(1<<i))    	// condition to find bit is set or not
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	displaybin(n);
}




/*function to calculate the sum of two int using binary operation*/
int binsum(int bin1,int bin2)
{
	int a = 1;
	if(a){
		;

	}

	if(bin1&&bin2)			//case of 1 1
	{
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
int sum(int n1 ,int n2);
/* program to find result of binary subtraction in easy way */
int binsub_v1(int bin1 , int bin2)
{
	bin2 = negateinteger(bin2)+1;
	return sum(bin1,bin2);
}
int sum(int input1,int input2)
{
//	printf("%d %d\n",input1,input2);
	int flag = 0;
	int temp1 = 0,temp2 = 0;
	int res = 0;
	for(int i = 0 ; i <= 31 ;i++)
	{	
		temp1 = input1 & (1<<i);
		temp2 = input2 & (1<<i);
		
		res = res | (binsum(temp1,temp2)<<i);		
		if(i==31 && temp1==temp2){
			printf("%d    %d",res&(1<<i),temp1);
			if((res&(1<<i)) != temp1){
				printf("\n \t Exception : bit overflow \n");
				overflow =1;
			}
				 
		} 
	}
	if(overflow = 1){
		return 0;	
	}
	printf("result in binary form : ");
	chartobin(res);
	printf("\n");
	return res;

}

void main()
{





	printf("\n\n\n\n----------------------------------------binary ADD/SUB -------------------------------------\n\n\nCHOICES: \n");
int ch = 12;
while(ch!= 4)
{
	printf("press 1 to ADD to integer in binary form \n \n"); 
        printf("press 2 to SUBTRACT to integer in binary form \n \n"); 
        printf("press 3 to do BOTH  \n \n"); 
        printf("press 4 to EXIT \n \n"); 
	scanf("%d",&ch);
	int opt3 = 0;
	if(ch == 3)
	{
		ch = 1;
		opt3 = 1; 

	}
	switch(ch)
	{
		case 1 :
		{
			        int input1 ,input2;
				printf("enter input 1 \n");
			        scanf("%d",&input1);
                                printf("enter input 2 \n");
                                scanf("%d",&input2);

			        printf("binary representation of input1 :       ");
			        chartobin(input1);
			        printf("\n");
			        printf("binary representation of input2 :       ");
			        chartobin(input2);
			        printf("\n");
				int ans = sum(input1,input2);
				if(overflow == 1){
					overflow = 0;
					break;
				}
			        printf("\n the sum of the number after conversion to decimal: %d\n\n",ans);
	if(opt3==1){
		                                printf("binary representation of input1 :       ");
                                chartobin(input1);
                                printf("\n");
                                printf("binary representation of input2 :       ");
                                chartobin(input2);
                                printf("\n");
                                printf("\n the diffference of the number after conversion to decimal: %d\n\n",binsub_v1(input1,input2));

	}
		
		}
	//	if(!(opt3))
			break ;
		case 2 :
                {
                                int input1 ,input2;
				printf("enter input 1 \n");
                                 scanf("%d",&input1);
                                printf("enter input 2 \n");
                                scanf("%d",&input2);
//scanf("%d%d",&input1,&input2);
                                printf("binary representation of input1 :       ");
                                chartobin(input1);
                                printf("\n");
                                printf("binary representation of input2 :       ");
                                chartobin(input2);
                                printf("\n");
				int ans = binsub_v1(input1,input2);
				if(overflow == 1){
					overflow = 0;
					break;
				}
                                printf("\n the diffference of the number after conversion to decimal: %d\n\n",ans);

                }
		break ;
		case 4 :
                {	
			;

                }
		break;
		default:
			printf("please enter valid input \n \n");



	}
	carry = 0;
	
}


}
