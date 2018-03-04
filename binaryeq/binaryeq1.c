#include"stdio.h"

/* program to find and print  binary form of arguments */
void chartobin(int c){
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


void main(){
	char input[30];
	
	printf("enter the character or number for which you want to find the binary representation \n");
	printf("to exit press \'00\' \n");
	scanf("%s",input);
while(!(input[0]=='0'&&input[1]=='0')){
	if((input[0] >= 65 && input[0] <= 90) || (input[0] >= 97 && input[0] <= 122)) //checks whether entered input is character or integer if character calls the function if integer finds the integer value of corresponding numerical caracters
	{ 
		
		chartobin(input[0]);
	}
	else{
		int i = 0;
		int flag = 0;
		if(input[0]=='-'){
			i++;
			flag = 1;

		}
		int temp = 0;
		for( ; input[i] !='\0' ; i++){
			temp = temp*10 + input[i] - '0'; //finds the integer through  difference between 'n' and '0'
		}
		if(flag == 1)
			temp*=-1;
		chartobin(temp);
	}
        printf("enter the character or number for which you want to find the binary representation \n");

        printf("to exit press \'00\' \n");

	scanf("%s",input);
}

	/*		int inc = 1;
		int binval[8];
		for(int i  = 0 ; i < 8 ; i++){
			binval[i] = 0;
		}

		inc = 0;
		while(temp > 0){
			int val = temp % 2;
			temp = temp / 2;
			binval[inc]= val;
			inc++;
		}
		printf("\n \t");
		for(int i = 7 ; i >= 0 ; i--)
			printf(" %d",binval[i]);
	
	}
	*/
}

		
