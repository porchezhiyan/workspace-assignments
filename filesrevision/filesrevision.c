/* Program to get text from user and write in a file and allow to view and manage revisions */

#include"stdio.h"
#include"stdlib.h"
#include"utils.h"  //userdefined functions


//#define debug 1
#define step 10 // step value used in realloc

int current_revision = 1;

typedef struct Buffer  // structure to store the user texts 
{
	int revision;
	char* content;
	int content_length;
	struct Buffer* next;  //pointer to next node in list
	struct Buffer* prev; //pointer to previous node in list
} Buff;



/*function to get text data for the file*/
char* getdata(char* datacpy)
{
#ifdef debug
	printf("entering getdata");
#endif

 	int counter = 0;
 	printf("enter content : (terminate with '~')\n");
 	char ch;
 	while((ch=getchar())!='~')//while end of line
 	{

 		*(datacpy+counter) = ch;
 		
 		counter++;

 		#ifdef debug
			printf("%d",step+counter);
		#endif
		if(counter%10 == 0)//step wise reallocate memory for data
 		{
 			char*reallocate;//temporary pointer to reallocate memory
 			reallocate = (char*)realloc(datacpy,sizeof(char)*(step+counter));
 			if(reallocate!=NULL)
 			{
 				datacpy = reallocate;
 				#ifdef debug
					printf("realloc successfull");
				#endif
 			}
 			else{
 				printf("error : no memory allocated");
 				return NULL;
 			}
 		}
 	}
 	*(datacpy+counter) = '\0'; //append '\0' after last char
 	
#ifdef debug
printf("%s outgoing input\n",datacpy);
#endif
 	
 	
 	return datacpy;
}


/*fn to write struct to file*/
FILE* filewrite(Buff* temp)
{
	char* manager;
	fopen("manager.txt","w+b");
	
	
}






void main()
{
 	FILE * fdata;	//pointer to access the content enter by user which is stored in the file
 	
 	fdata = fopen("data.txt","r+b");

 	if(fdata == NULL)
 	{
 		fdata = fopen("data.txt","w+b");// if no file create file using "W" mode
 		if(fdata == NULL)
	 	{
 			fdata = fopen("data.txt","w+b");// if no file create file using "W" mode
	 		printf("cannot open file");
 			return;
		}
	}


	char* data =(char*) malloc(sizeof(char));//initially allocates 10 bytes to data 
	if(data==NULL)
	{
		printf("error: cannot allocate memory");
		return;
	}
	
	if(data = getdata(data));
//#ifdef debug
	printf("%s",data);
//#endif	

	Buff* buffer1;
	buffer1->revision = current_revision;
	buffer1->content = data;
	buffer1->content_length = str_len(data);
	buffer1->next = NULL;
	buffer1->previous = NULL;
	
	
	
	
	

	fwrite(data,str_len(data),1,fdata); 	
	
	
	
}
