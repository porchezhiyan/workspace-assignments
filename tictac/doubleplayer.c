/*  implementation of tit tac toe game using 'c'*/
#include"stdio.h"
#include"stdlib.h"

//#define debug 0

#define set 1
char** board;	//double pointer to represent the board using matrix

char user_piece;	
char comp_piece;

int end_condition = 0;

int turn = 1;

/*function to check whether a postition is unoccupied*/
int check_free(int col , int row)
{
	char val_at_p = *(*(board+col)+row); //getting value at position
	if(val_at_p ==	'O' || val_at_p == 'X')	//if position not free...
	{
		return 0;
	}
	return 1;
}


/*funcion to check valid position*/
int check_valid(int col , int row,int size)
{
	if(col > 0 && row > 0) //cant be -ve
	{
		if(col < size && row < size)  //must be less than size
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
/*function to display contents of the board at any instant...*/
void displayboard(int size)
{
	for(int column = 0 ; column < size ; column++)
	{
		for(int row = 0 ; row < size ; row++)
		{
			if(row!=0)
				printf("|"); 
				
			printf("%c",*(*(board+column)+row)); //board[column][row]

			
		}
		printf("\n-----\n");
	}

}




/* set coms piece out side the given location */
void setoutside(int coll,int row , int size)
{

///	printf("in setoustside fn\n");
	unsigned int cval,rval;
	
	do
	{	
		cval = rand()%(size);
		rval = rand()%(size);
	//	printf("\n  %d %d \n",cval,rval);
	}while(!check_free(cval,rval));  // if random values equal to either of user enter val generate again
	
//	printf("in setoustside fn\n");

	*(*(board+cval)+rval) = comp_piece;
	
	displayboard(size);
	

	
	
}





/* game play...*/
void game(int size)
{
	
	board = (char**)malloc(size*sizeof(char*)); 	//assigning memory for storing the rows in column
	if(board == NULL)
	{
		printf("error: cannot allocate memory");
		exit(0);
	}
	int row = 0;
	while(row < size)
	{
		*(board+row) = (char*)malloc(size*sizeof(char)); //assigning memory for each row 
		if(*(board+row) == NULL)
		{
			printf("error: cannot allocate memory");
			exit(0);
		}
		row++;
	}
	char position = '1';
	
	/*assigning initial values for board positions and displaying position*/
	for(int column = 0 ; column < size ; column++)
	{
		for(int row = 0 ; row < size ; row++)
		{
			*(*(board+column)+row) = position++;
			printf("%c ",*(*(board+column)+row)); //board[column][row]
			
		}
		printf("\n");
	}
	
	
	while(!end_condition) //loops until game ends
	{
		int userpos;
		printf("enter the position where u want to place your piece \n");
		scanf("%d",&userpos);
		
		
	/* convert position value you to usable offsets*/
		int row_off,col_off;	// row offset and colum of set
		if(userpos % size > 0)	// with remainder condition
		{
			col_off = userpos/size;
			row_off = (userpos%size) - 1;
		}
		else
		{
			col_off = userpos/size-1;
			row_off = size - 1;
		}
		
# ifdef debug
		printf("%d %d\n",col_off,row_off);
# endif		
		char val_at_up = *(*(board+col_off)+row_off); //getting value at user position
		if(val_at_up ==	'O' || val_at_up == 'X')	//if position not free...
		{
			printf("invalid position\n");
			continue;
		}
		
		else
		{
			*(*(board+col_off)+row_off) = user_piece;
			displayboard(size);	
			
			printf("\n com's move\n");
			if(turn <= (size*size))
			{
		//					printf("\n com's move\n");	
				setoutside(col_off,row_off,size); // set randomly at valid location
			}
			
			
			
		/*
		
			
			int val1 = *(*(board+col_off-1)+row_off);  //         colloff-1,row_off);	// upper check
			int val2 = *(*(board+col_off-2)+row_off);					// 	getpiece(colloff-2,row_off);	
			
			if(checkwinning(val1,val2))
			{
				if(val1==user_piece)
				{
					
				}	
			}
			else if(checklosing(val1,val2))
			{
				
			}
			
			
			getpiece(colloff+1,row_off);	// lower check
			getpiece(colloff+2,row_off);
			
			getpiece(colloff,row_off-1);	// left check
			getpiece(colloff,row_off-1);
			
			getpiece(colloff,row_off+1);	// right check
			getpiece(colloff,row_off+2);
			
			getpiece(colloff+1,row_off+1);	// upper leading dg check
			getpiece(colloff+2,row_off+2);
			
			getpiece(colloff-1,row_off-1);	// lower trailing check
			getpiece(colloff-2,row_off-2);
			
			getpiece(colloff+1,row_off-1);	// lower leading check
			getpiece(colloff+2,row_off-2);
			
			getpiece(colloff-1,row_off+1);	// upper trailing check
			getpiece(colloff-2,row_off+2);
			
			getpiece(colloff-1,row_off);	// vertcl middle check
			getpiece(colloff+1,row_off);
			
			getpiece(colloff,row_off-1);	// hztl middle check
			getpiece(colloff,row_off+1);
			
			
			*/
			
		}
		turn++; //completion of a turn
		
	}
}



void main()
{

	printf("\n\n\n-------------------TIC TAC TOE---------------------------\n\n\n");
	
	printf("\nEnter your choice of piece...('X'/'O'):\n");	
	scanf("%c",&user_piece);
	if(user_piece == 'x')
	{
		user_piece = 'X'; // to capital X
		comp_piece = 'O';
	}
	else
	{
		user_piece = 'O'; // to capital X
		comp_piece = 'X';
	}
	
	printf(" User Piece : %c\n",user_piece);
	printf(" Computer's Piece : %c\n",comp_piece);
	
	printf("\n\nEnter Board size:");
	printf("\n\npress 3 : 3 x 3");
	printf("\npress 5 : 5 x 5");
	printf("\npress 7 : 7 x 7\n");	
	
	int difficulty;
	scanf("%d",&difficulty);
	printf(" mode chosen : ");
		
	switch(difficulty)
	{
		case 3:		//diffulty level 3X3
		{
			printf("\t 3x3 game: \n");
			game(difficulty);
			break;
		}
		
		case 5:		//diffulty level 7X7
		{
			printf("\t 5x5 game \n");
			
			break;
		}
		
		case 7:		//diffulty level 7X7
		{
			printf("\t 7x7 game \n");
			break;
		}
		default:
			printf("invalid choice");
	}
		
}


