/* Program to get text from user and allow to make revisions */

#include"stdio.h"
#include"stdlib.h"
#include"utils.h"  //userdefined functions


#define __ENDVAL__ 126

#define __debug__ 1

#define MAX_REVISIONS 20

int revision_count = 0; //to keep track of the auto increasing revision number 

int current_revision = 0;

int start_revision = 0;


struct file  // structure to store the user texts 
{
	int revision;
	char* content;
	int content_length;
	struct file* next;  //pointer to next node in list
	struct file* previous; //pointer to previous node in list
};

typedef struct file file ;  // using 'file' as datatype for structure 

file* head = NULL; // initally head points to null when list is empty

file* end = NULL;	// pointer to point the last node



void deletefirstrev();

/*
 creating node and returnig pointer to the node:
 	-> increment revision value for current revision
 	-> assign revision value of node with current revision
 	-> getting text till '~' is pressed and dynamically store in content variable of node
 	-> return the pointer of created node

*/

file* create_node()
{
		file *temp = (file*) malloc(sizeof(file)); //creating temporary file node and allocating memory...
		
		
		if(temp == NULL) //when memory cannot be allocated to temp return 1...
		{
			printf("Exception : out of memory");
			exit(0);
		}
		
		current_revision++; 
		
		temp->revision = current_revision; //assigns revision number
		
		while(getchar()!='\n')
			;
		
		printf("\n Enter your content for the report (press '~' to mark the end of string.)...\n");
		
		temp->content = (char*)malloc(sizeof(char)); //allocates size of one character initially...
		
		if(temp->content == NULL) //when memory cannot be allocated to temp return 1...
		{
			printf("Exception : out of memory");
			exit(0);
		}
		
		char* char_getter = temp->content; //gets starting address of content char pointer


		char singlechar;//get character one by one;
		
		temp->content_length = 1; // adding first char
		
	 	int counter = 1;
		
		
		while((singlechar = getchar())!= __ENDVAL__) //gets character till ~ is pressed...
		{
			*char_getter = singlechar; //allocates character to address pointed by char_getter...
			
			(temp->content_length)++; //indicates addition of one more character...
			 
			                                                           
			char* reallocate = (char*)realloc(temp->content,(temp->content_length)*sizeof(char)); //allocates memory to store one more character
			
			if(reallocate == NULL) //if realloc failed throw exception
			{
				printf("Exception : out of memory");
				exit(0);
			}
			
			temp->content = reallocate;// assign reallocated address back to temp -> content
			reallocate = NULL;	// made NULL for next use
			char_getter++;	//points the next address to store the next character
		}
				//printf(" char getter %s",temp->content);
		*char_getter = '\0'; //mark the end of the content
		revision_count++;	//tracks number of revisions
		if(revision_count>MAX_REVISIONS)
		{
			deletefirstrev();
		}
	//	printf("node created");
		return temp;
}



/* function to print the contents of the node*/
void printnode(file* node) 
{

//# if (debug == 1)
//	printf("in fn printnode\n");
//# endif

	printf("\n\n\trevision = %d\n\tcontent = %s\n\tcontent length = %d",node->revision,node->content,node->content_length); //print contents of head node

}

/*delete first revision*/
void deletefirstrev()
{
	file* temp = head;
	head = head->next;
	head->previous = NULL;
	if(temp->content != NULL)
		free(temp->content);
	if(temp!=NULL)
		free(temp);
}




/* function to print the content of the node with reqrevision*/
void printnodeofrevision(int reqrevision)
{


# ifdef debug
//	printf("in fn printnodeofrev\n");
# endif

	file *temp = head;
	while(temp != NULL) //identify the pointer to node with reqrvision
	{
		if(temp->revision == reqrevision) // node found
		{
			printnode(temp); // required node is passed to printfn
			break;
		}
		temp = temp->next;
		
	}
	if(temp == NULL)
	+	printf("sorry :-( revision is obsolete and deleted or invalid revision number \n");
}


/* insert node at the last*/
void insertlast(file* ptr)
{


	printf("in fn insertlast\n");

	end->next = ptr; //insert next to current end node
	ptr->previous = end ;
	end = ptr;	// make inserted node as end node
	ptr->next = NULL;	//end node has no next node...
	//printnode((end->previous)->next); //check fn works
}


/*print all node*/

void printlist()
{	file* ptr = head;
	while(ptr != NULL)
	{
		printnode(ptr);
		ptr=ptr->next;	
	}
}



/* main function */
void main()
{
	//	head = (file*)malloc(sizeof(file)); //memory is allocated for head to store a structure values
	
	if(current_revision == 0) //when list is empty 
	{
		printf("file empty create report \n"); //initially empty
		head = create_node(); //allocate temp to head as it is first node
		head->next = NULL;//no second node initially..
		head->previous = NULL; //no previous node for head node.. 
		end = head; //head is the only node so it is the end...
	//	printnode(head);		
				
	}
	else
	{
		;
	
	}
	int choice = 0;
	do
	{
		if(choice!=0)
		{



			printf("\n current revision:%d",current_revision+1);

			printf("\nthe details of last revision...\n"); //print last revision details before current revision...
			printnodeofrevision(current_revision);


		}
		printf("\n\tpress 1 to enter a report");
		printf("\n\tpress 2 to view a report of particular revision");
		printf("\n\tpress 0 to enter a exit\n");
		
		scanf("%d",&choice);
	//	while(getchar()!='\n')
	//		;
			

		
		switch(choice)
		{
			case 1:
			{	
			
				file* temp = create_node();
			//	while(getchar()!='\n')
			//		;
		
				insertlast(temp);
				//	printlist();
				break;
				
			}
				
			case 2:
			{
				while(getchar()!='\n')
					;
				printf("\n current revision : %d ",current_revision+1);
				
				
				printf("\n enter which revision you want to view(records maintained till last 20 revisions only...) :\n");
				int check_revision;
				
				scanf("%d",&check_revision);	

	# ifdef debug
		printf(" inpuutted value %d ",check_revision);
	# endif			
				printnodeofrevision(check_revision);			
				//if(revision > 0
				break;
			}
			case 0:
			{	
			
				file* temp;
				temp = head->next;
				while(temp!=NULL)
				{
				
					free(head);
					head = temp;
					temp = head->next;
					
				}
				break;
			}
			default:
			{
				printf("enter valid input\n");
			
			}			
		}
	}while(choice!=0);
	
	
	
}

