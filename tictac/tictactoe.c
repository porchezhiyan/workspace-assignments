/*  implementation of tit tac toe game using 'c'*/

/*
BUGS:
-> pre-result ending : fixed
-> segfault for certain condition {4983,697} :	fixed
-> cannot detecting user's winning position in turn two :fixed
*/
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
//#define debug 0

#define size 3
//#define debug 1

char** board = NULL;	//double pointer to represent the board using matrix

char user_piece;	
char comp_piece;

int end_condition = 0;

int turn = 1;

/*function to check whether a postition is unoccupied*/
int check_free(int col , int row)
{
	char val_at_up = *(*(board+col)+row); //getting value at user position
	if(val_at_up ==	'O' || val_at_up == 'X')	//if position not free...
	{
		return 0;
	}
	return 1;
}


/*funcion to check valid position*/
int check_valid(int col , int row)
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
void displayboard()
{
	for(int column = 0 ; column < size ; column++)
	{
		for(int row = 0 ; row < size ; row++)
		{
			if(row!=0)
				printf("|"); 
				
			printf("%c",*(*(board+column)+row)); //board[column][row]

			
		}
		if(column != size-1)
			printf("\n-----\n");
	}

}




/* set coms piece out side the given location */
void setoutside(int coll,int row)
{
# ifdef debug
	printf("in setoustside fn\n");
# endif		
	unsigned int cval,rval;
	srand(time(0));
	
	do
	{	
		cval = rand()%(size);
		rval = rand()%(size);
# ifdef debug
		printf("\n  %d %d \n",cval,rval);
# endif		
	}while(!check_free(cval,rval));  // if random values equal to either of user enter val generate again
	
# ifdef debug
	printf("in setoustside fn\n");
# endif		
	*(*(board+cval)+rval) = comp_piece;
	
	displayboard(size);
	

	
	
}

/*check if computer has won*/
int cwon()
{
# ifdef debug
printf("in c won ");
# endif		
	/*check hztl match*/
	for(int column = 0 ; column < size ; column++)
	{
		
		int rc = 0 ; //number of same piece ; count in same row
		for(int row = 0 ; row < size ; row++)
		{	
			
			if(comp_piece == *(*(board+column)+row)) //board[column][row]
			{
				rc++; //match found
				if(rc == size) //bingo!...
				{
					return 1;
				}
			}
			else
			{
				rc = 0; //not matched re count
			}
		}
		if(rc == size)
			return 1;
	}
	
	
# ifdef debug
	printf("hztl chk faild");
# endif			
	/*check vrtcl match*/
	for(int row = 0 ; row < size ; row++)
	{
		int cc = 0 ; //number of same piece;count in same row
		for(int column = 0 ; column < size ; column++)
		{	
			
			if(comp_piece == *(*(board+column)+row)) //board[column][row]
			{
				cc++; //match found
				if(cc == size) //bingo!...
				{
					return 1;
				}
			}
			else
			{
				cc = 0; //not matched re count
			}
		}
		if(cc == size)
			return 1;
	}
	
# ifdef debug
	printf("vrtcl chk faild");
# endif			
	/*check leading diagonl*/
	int ldc = 0 ; //number of same piece;count in same row
	for(int column = 0,row = 0 ; column < size ;row++,column++)
	{	
			
		if(comp_piece == *(*(board+column)+row)) //board[column][row]
		{
			ldc++; //match found
			if(ldc == size) //bingo!...
			{
				return 1;
			}
		}
		else
		{
			ldc = 0; //not matched re count
		}
	}
	if(ldc == size)
		return 1;

	
# ifdef debug
	printf("ld chk chk faild");
# endif			
	/*check trailing diagonal*/
	int tdc = 0 ; //number of same piece;count in same row
	for(int column = 0,row = size-1 ; row >= 0 ;row--,column++)
	{	
			
		if(comp_piece == *(*(board+column)+row)) //board[column][row]
		{
			tdc++; //match found
			if(tdc == size) //bingo!...
			{
				return 1;
			}
		}
		else
		{
			tdc = 0; //not matched re count
		}
	}
	if(tdc == size)
		return 1;
# ifdef debug
	printf("td chk faild");
# endif		
	return 0;

}


/*check if user has won*/

int uwon() //returns 1 if user won else returns 0
{

# ifdef debug
printf("in u won ");	
# endif		
	/*check hztl match*/
	for(int column = 0 ; column < size ; column++)
	{
		
		int rc = 0 ; //number of same piece ; count in same row
		for(int row = 0 ; row < size ; row++)
		{	
# ifdef debug
				printf("before segfault %d %d",column,row);			
# endif		
			if(user_piece == *(*(board+column)+row)) //board[column][row]
			{
				rc++; //match found
				if(rc == size) //bingo!...
				{
					return 1;
				}
			}
			else
			{
				rc = 0; //not matched re count
			}
		}
		if(rc == size)
			return 1;
	}
	
	
# ifdef debug
	printf("hztl chk faild");
# endif			
	/*check vrtcl match*/
	for(int row = 0 ; row < size ; row++)
	{
		int cc = 0 ; //number of same piece;count in same row
		for(int column = 0 ; column < size ; column++)
		{	
			
			if(user_piece == *(*(board+column)+row)) //board[column][row]
			{
				cc++; //match found
				if(cc == size) //bingo!...
				{
					return 1;
				}
			}
			else
			{
				cc = 0; //not matched re count
			}
		}
		if(cc == size)
			return 1;
	}
	
# ifdef debug
	printf("vrtcl chk faild");
# endif			
	/*check leading diagonl*/
	int ldc = 0 ; //number of same piece;count in same row
	for(int column = 0,row = 0 ; column < size ;row++,column++)
	{	
			
		if(user_piece == *(*(board+column)+row)) //board[column][row]
		{
			ldc++; //match found
			if(ldc == size) //bingo!...
			{
				return 1;
			}
		}
		else
		{
			ldc = 0; //not matched re count
		}
	}
	if(ldc == size)
		return 1;

	
# ifdef debug
	printf("ld chk chk faild");
# endif			
	/*check trailing diagonal*/
	int tdc = 0 ; //number of same piece;count in same row
	for(int column = 0,row = size-1 ; row >= 0 ;row--,column++)
	{	
			
		if(user_piece == *(*(board+column)+row)) //board[column][row]
		{
			tdc++; //match found
			if(tdc == size) //bingo!...
			{
				return 1;
			}
		}
		else
		{
			tdc = 0; //not matched re count
		}
	}
	if(tdc == size)
		return 1;
# ifdef debug
	printf("td chk faild");
# endif		

	return 0;
}

/* stratergy 1 : if user has advanatageous position
	-> return 1 if there is chance along row 
	-> return 2 if there is chance along column
	-> return 3 if there is chance along leading diag
	-> return 4 if there is chance along trailing diag
	-> return 0 if no chance

*/


/* check the number of user piece in a single row / column if it plots to win and there is vacant position fing the=at advantage position and  fill with comp_piece*/
int uwinning()
{
# ifdef debug
	printf("inu winning\n");
# endif		
	for(int c = 0 ; c < size ; c++)  //checking all columns each
	{	int count = 0;
		int advpos = -1;
		for(int r = 0 ; r < size ; r++)
		{
			
			char piece = *(*(board+c)+r);
			if(piece == user_piece)
			{
				count++;
			}
			else if(piece!= comp_piece)
			{
				advpos = r;
			}
		}
		if(count == size - 1 && advpos != -1) //advantage position
		{
			*(*(board+c)+advpos) = comp_piece;
			if(cwon(size))
			{
				printf("\n GAME OVER!!! You Lose  \n"); 
				end_condition = 1;
			}
			return 1 ; 
		}
	}

# ifdef debug	
		printf("inu winning\n");
# endif		
	for(int r = 0 ; r < size ; r++)  //checking all rows each
	{	int count = 0;
		int advpos = -1;
		for(int c = 0 ; c < size ; c++)
		{
			
			char piece = *(*(board+c)+r);
			if(piece == user_piece)
			{
				count++;
			}
			else if(piece!= comp_piece)
			{
				advpos = c;
			}
		}
		if(count == size - 1 && advpos != -1) //advantage position
		{
			*(*(board+advpos)+r) = comp_piece;
			if(cwon(size))
			{
				printf("\n GAME OVER!!! You Lose  \n"); 
				end_condition = 1;
			}
			return 1 ; 
		}
	}
	
# ifdef debug
			printf("inu winning\n");
# endif		
	int count = 0;
	int advpos = -1;	
	for(int r = 0 ,c = 0 ; r < size ; r++,c++)
	{
		char piece = *(*(board+c)+r);
			if(piece == user_piece)
			{
				count++;
			}
			else if(piece!= comp_piece)
			{
				advpos = r;
			}
		
	}
	if(count == size - 1 && advpos != -1) //advantage position
	{
		*(*(board+advpos)+advpos) = comp_piece;
		if(cwon(size))
		{
			printf("\n GAME OVER!!! You Lose  \n"); 
			end_condition = 1;
		}
		return 1 ;
	}

# ifdef debug	
			printf("inu winning\n");
# endif		
	count = 0;
	int advposr = -1;
	int advposc = -1;
	for(int r = size-1 ,c = 0 ; c < size ; r--,c++)
	{
		char piece = *(*(board+c)+r);
			if(piece == user_piece)
			{
				count++;
			}
			else if(piece!= comp_piece)
			{
				advposr = r;
				advposc = c;
			}
		
	}
	if(count == size - 1 && advpos != -1) //advantage position
	{
		*(*(board+advposc)+advposr) = comp_piece;
		if(cwon(size))
		{
			printf("\n GAME OVER!!! You Lose  \n"); 
			end_condition = 1;
		}
		return 1 ;
	}
	
# ifdef debug	
		printf("out u winning\n");
# endif			
	return 0;

	
	
}




/* stratergy 1 : if computer has advanatageous position
	-> return 1 if there is chance along row 
	-> return 2 if there is chance along column
	-> return 3 if there is chance along leading diag
	-> return 4 if there is chance along trailing diag
	-> return 0 if no chance

*/


/*returns 1 if advantage position is found and value is set*/

/* check the number of computer piece in a single row / column if it plots to win and there is vacant position fing the advantage position and  fill with comp_piece*/
int cwinning()
{
# ifdef debug
	printf("in c winning ");
# endif		
	for(int c = 0 ; c < size ; c++)  //checking all columns each
	{	int count = 0;
		int advpos = -1;
		for(int r = 0 ; r < size ; r++)
		{
			
			char piece = *(*(board+c)+r);
			if(piece == comp_piece)
			{
				count++;
			}
			else if(piece!= user_piece)
			{
				advpos = r;
			}
		}
		if(count == size - 1 && advpos != -1) //advantage position
		{
			*(*(board+c)+advpos) = comp_piece;
			if(cwon(size))
			{
				printf("\n GAME OVER!!! You Lose \n"); 
				end_condition = 1;
			}
			return 1 ; 
		}
	}
	
	
	for(int r = 0 ; r < size ; r++)  //checking all rows each
	{	int count = 0;
		int advpos = -1;
		for(int c = 0 ; c < size ; c++)
		{
			
			char piece = *(*(board+c)+r);
			if(piece == comp_piece)
			{
				count++;
			}
			else if(piece!= user_piece)
			{
				advpos = r;
			}
		}
		if(count == size - 1 && advpos != -1) //advantage position
		{
			*(*(board+advpos)+r) = comp_piece;
			if(cwon(size))
			{
				printf("\n GAME OVER!!! You Lose \n"); 
				end_condition = 1;
			}
			return 1 ; 
		}
	}
	
	
	int count = 0;
	int advpos = -1;
	for(int r = 0 ,c = 0 ; r < size ; r++,c++)
	{
		char piece = *(*(board+c)+r);
			if(piece == comp_piece)
			{
				count++;
			}
			else if(piece!= user_piece)
			{
				advpos = r;
			}
		
	}
	if(count == size - 1 && advpos != -1) //advantage position
	{
		*(*(board+advpos)+advpos) = comp_piece;
		if(cwon(size))
		{
			printf("\n GAME OVER!!! You Lose \n"); 
			end_condition = 1;
		}
		return 1 ;
	}
	
	
	count = 0;
	int advposr = -1;
	int advposc = -1;
	for(int r = size-1 ,c = 0 ; c < size ; r--,c++)
	{
		char piece = *(*(board+c)+r);
			if(piece == comp_piece)
			{
				count++;
			}
			else if(piece!= user_piece)
			{
				advposr = r;
				advposc = c;
			}
		
	}
	if(count == size - 1 && advpos != -1) //advantage position
	{
		*(*(board+advposc)+advposr) = comp_piece;
		if(cwon(size))
		{
			printf("\n GAME OVER!!! You Lose \n"); 
			end_condition = 1;
		}
		return 1 ;
	}
	
	return 0;

	
}



/* game play...*/
int game()
{
	
	board = (char**)malloc(size*sizeof(char*)); 	//assigning memory for storing the rows in column
	if(board == NULL)
	{
		printf("error: cannot allocate memory");
		return -1;
	}
	int row = 0;
	while(row < size)
	{
		*(board+row) = (char*)malloc(size*sizeof(char)); //assigning memory for each row 
		if(*(board+row) == NULL)
		{
			printf("error: cannot allocate memory");
			return -1;
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
	
		printf("\nturn : %d \n",turn);
		int userpos;
		printf("\n->enter the position where u want to place your piece ");
		
		printf("\t->to restart press -'111'\n");
		
		printf("\t->to quit the game press -'555'\n");
		
		if(scanf("%d",&userpos)!=1)	//validation done after conversion to coordinates
		{
			while(getchar()!='\n')
				;
			printf("invalid position\n");
			continue;
		}
		else if(userpos == 111)//option to restart game
			return -1;
		
		else if(userpos == 555)//option to quit game
		{
			int row = 0;
			if(board !=NULL)
			{
				while(row < size)
				{
					if(*(board+row) != NULL)
					{
						free(*(board+row));
					}
					row++;
				}
				free(board);
			}
			exit(0);
		}
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
			
			
			if(turn == 4)
			{	printf("\nthe game ended in a darw\n");	// no more room for new move board completely filled
				break;
			}
			

			printf("\n\ncom's move :\n");
		
			if(turn == 0)
			{
					
				setoutside(col_off,row_off); // set randomly at valid location
				turn++;
				continue; //no more operation for first turn continue to second turn
			}

# ifdef debug			
				printf("\n before UWON \n");
# endif		
			
			if(uwon(size))  //if user won after his move
			{
				printf("\nYOU WON !!!\n");
				
				end_condition = 1 ;
# ifdef debug
				printf("\n before c winning !!!\n");
# endif		

			}

			
			else if(cwinning(size))	// if possible for computer to win
			{
# ifdef debug
				printf("i can win");
# endif		


				displayboard(size);


# ifdef debug
					printf("\n befor u wiinning!!!\n");
# endif						
			}
					
		
			else if(uwinning(size))	// if possible  for user to win
			{	
# ifdef debug
				printf("u can win");
# endif		
				displayboard(size);
				

# ifdef debug
				printf(" before develop play\n");
# endif		
			}
			else	//develop play
			{
# ifdef debug
				printf("develop play\n");
# endif	
				setoutside(col_off,row_off); // set randomly at valid location				
			}
		
			
	
			
		}
		turn++; //completion of a turn
		if(turn >= ((size*size)/2+1))
		{
			printf("the game ended in a draw \n ");
			end_condition = 1;
		}
		
	}

}



void main()
{

	printf("\n\n\n-------------------TIC TAC TOE---------------------------\n\n\n");

	int ch = 0;
	do
	{
		while(ch!=0&&getchar()!='\n')//empty buffer
			;	
	printf("\nEnter your choice of piece...('X'/'O'):\n");
	scanf("%c",&user_piece);
	
# ifdef debug
	printf("%c",user_piece);
# endif		
	if(user_piece == 'x' ||user_piece == 'Y')
	{
		user_piece = 'X'; // to capital X
		comp_piece = 'O';
	}
	else if(user_piece == 'o'||user_piece == 'O')
	{
		user_piece = 'O'; // to capital X
		comp_piece = 'X';
	}
	else
	{
		printf("invalid choice \n");
		ch = 1 ;//to indicate not the first attempt
		continue;
	}
	
	printf(" User Piece : %c\n",user_piece);
	printf(" Computer's Piece : %c\n",comp_piece);
	
	printf("press 1 : to start the game \n");
	printf("press 0 : to exit \n");
	
	
	scanf("%d",&ch);
# ifdef debug
	printf("%d",ch);
# endif			
	
	switch(ch)
	{
		case 1:		//diffulty level 3X3
		{
			printf("\t 3x3 game: \n");
			turn = 0; // refresh turn for new game...
			end_condition = 0;
			game(size);
			break;
		}
		
		case 0:		//free memory and exit
		{
			
			int row = 0;
			if(board !=NULL)
			{
				while(row < size)
				{
					if(*(board+row) != NULL)
					{
						free(*(board+row));
					}
					row++;
				}
				free(board);
			}
			
			
			break;
		}
		default:
			printf("invalid choice");
	}
	
	}while(ch!=0);
		
}


