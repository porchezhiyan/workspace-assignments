/* Program to get text from user and write in a file and allow to view and manage revisions */

#include"stdio.h"
#include"stdlib.h"
#include"utils.h"  //userdefined functions


typedef struct Buffer  // structure to store the user texts 
{
	int revision;
	char* content;
	int content_length;
	struct Buffer* next;  //pointer to next node in list
	struct Buffer* previous; //pointer to previous node in list
} buff;


 void main()
 {
 	buff a ;
 //	a.revision = 1;

// 	str_cpy(a.content,"asd"); 
 //	a.content_length = 3;
 //	a.next = NULL;
 //	a.previous = NULL;
 	FILE *fp;
 	fp = fopen("sample.txt","rb");
 	fread(&a,sizeof(buff),1,fp);
 	printf("%p",(a.content));
 	
 }
 
