#include"stdio.h"
#include"utils.h"
#include"string.h"

#define nameoffset 15



typedef struct  student{ //student structure
	
        int id;

	char *name;
	int age;
	char *address;
	char *gender;

}struct_student;	//typedef to STUENT

int uniqid = 1;


/*getter fn for getting string till enter pressed*/
char* get_string()
{
	int step = 10; // to realloacte memory as 10 bytes each time
	char* str = (char*)malloc(step*sizeof(char));	//storing the user inputted string
	if(str == NULL)
	{
		return NULL;
		printf("cannot allocate memory");
	}
	char c; // stores each char one by one
	int count = 0; //to point next location 
	getchar(); //eats new line
	while((c=getchar())!='\n'){
		*(str+count) = c; //assigns char to str
		count++;
		if(count%step == 0){		//reallocating at 10 bytes each time
			char* tmp = (char*)realloc(str,(count+step));
			if(tmp == NULL)
			{
				printf("error:cannot allocat memory");
				return NULL;
			}
			else
			{
				str = tmp;
			}
		}
	}
	*(str+count) = '\0'; 
	return str;

}

/*getter for age*/
int get_age()
{	
	int n ;
	do
	{
		scanf("%d",&n);
		if(n > 5 && n < 31)
		{
			break;
		}
		else
		{
			printf("\n enter value between 6 to 30\n");
		}
	}while(1);
	return n;
}

/*getter fn for gender*/
char* get_gender()
{
	char g;
	do
	{
		scanf("%c",&g);
		if(g=='m'||g=='f'||g=='F'||g=='M')
		{
			break;
		}
		else
		{
			printf("\n invalid character! please enter again \n");
		}
	}while(1);
	
	if(g=='m'||g=='M')
		return "male";
	else
		return "female";

}

/* convert structure variables to character pointers and append each of them between stringconstants as tags representing them*/





/*function for writing to file*/
int writeto(stu_ptr,tot,fp)
struct_student* stu_ptr;
int tot;
FILE* fp;
{
	char* buffer ="";
	
	for(int itr = 0 ; itr < tot ; itr++)
	{
		buffer = str_cat(buffer,"<student>");	  //each student data goes between student tags
		buffer = str_cat(buffer,"<name>");
		buffer = str_cat(buffer,((stu_ptr+itr)->name)); //name
		buffer = str_cat(buffer,"</name>");
			
		buffer = str_cat(buffer,"<age>");
		buffer = str_cat(buffer,itos((stu_ptr+itr)->age)); //age converted to character array using userdefined itos function
//printf("%s",itos((stu_ptr+itr)->age));
		buffer = str_cat(buffer,"</age>");
		
		buffer = str_cat(buffer,"<id>");
		buffer = str_cat(buffer,itos((stu_ptr+itr)->id)); //id to string using itos and appended
		buffer = str_cat(buffer,"</id>");
		
		buffer = str_cat(buffer,"<address>");
		buffer = str_cat(buffer,((stu_ptr+itr)->address)); //address
		buffer = str_cat(buffer,"</address>");
		
		
		buffer = str_cat(buffer,"<gender>");
		buffer = str_cat(buffer,((stu_ptr+itr)->gender)); //gender
		buffer = str_cat(buffer,"</gender>");
		buffer = str_cat(buffer,"</student>");
	}		
	printf("to file: %s",buffer);		//end for of how it is written in file
	fwrite(buffer,str_len(buffer),1,fp); //wrtiting in file


}


/*function for reading from file*/
struct_student* readfrom(stu_ptr,ftot,fp)
struct_student* stu_ptr;
int* ftot;
FILE* fp;
{
	fseek(fp,0,SEEK_END);	//marker moved to end
	int len = ftell(fp);  //ftell gives the length of file
	fseek(fp,0,SEEK_SET);	//marker moved to begining again
	char* buffer = (char*)malloc(sizeof(char)*len); 
	if(buffer == NULL)
	{
		printf("error: cannot allocate memory");
		return NULL;
	}
	fread(buffer,len,1,fp);	//reading from file and storing in buffer
	printf("from file : %s",buffer);	
	
		
	int tot = 0; //variable to store number of records
	
	struct_student* ptr =NULL;	//ptr to structure for getting data from buffer to structure
	while(*buffer != '\0')
	{
		if((*buffer) =='<' && *(buffer+1) =='s') //identifing student tag
		{

			
	/* gettting name from the buffer and storing in temporary string...*/		
	
			buffer+=nameoffset;	//macro for moving to start of name 
			int count = 0 ; //var to move to next address
			char* str =(char*)malloc(sizeof(char)); // str has base address and we traverse thru tempname
			if(str == NULL)
				return NULL;
			char* tempname = str;	// variable to store name before storing in structure
			while(*buffer!='<')	//getting char till start of closing name tag
			{
				*(tempname+count) = *buffer; 
				buffer++;
				count++;
				char* re =(char*)realloc(str,sizeof(char)*count);
				if(re != NULL)
					tempname = re;
				else
				{
					printf("error : cannot allocate memory");
					return NULL;
				}
			}
			*(tempname+count) = '\0';	
			
			tempname = str; //re assinging base address so we can use str for other variables


	/* gettting age from the buffer and storing in temporary string...*/

			buffer+=ageoffset; //macro for moving to start of name 
			
			count = 0 ;  //var to move to next address
			char* tempage =(char*)malloc(sizeof(char)); 
			if(tempage==NULL)
			{
				printf("error : cannot allocate memory");
				return NULL;
			}	
			str = tempage;
			
			while(*buffer!='<')//traverse till closing tag
			{
				*(tempage+count) = *buffer;
				buffer++;
				count++;
				char* re =(char*)realloc(str,sizeof(char)*count);
				if(re != NULL)
					tempage = re;
				else
				{
					printf("error : cannot allocate memory");
					return NULL;
				}
			}
			*(tempage+count) = '\0';
			
			tempage = str;



	/* gettting id from the buffer and storing in temporary string...*/
	
	
			buffer+=idoffset;
			
			count = 0 ;
			char* tempid =(char*)malloc(sizeof(char));
			if(tempid==NULL)
			{
				return NULL;
			}
			str = tempid;
			
			while(*buffer!='<')
			{
				*(tempid+count) = *buffer;
				buffer++;
				count++;
				char* re =(char*)realloc(str,sizeof(char)*count);
				if(re != NULL)
					tempid = re;
				else
				{
					printf("error : cannot allocate memory");
					return NULL;
				}
			}
			*(tempid+count) = '\0';
			
			tempid = str;

	/* gettting address from the buffer and storing in temporary string...*/
	
			buffer+=addressoffset;
			
			count = 0 ;
			char* tempaddress =(char*)malloc(sizeof(char));
			if(tempaddress==NULL)
			{
				printf("error : cannot allocate memory");
				return NULL;
			}
			str = tempaddress;
			
			while(*buffer!='<')
			{
				*(tempaddress+count) = *buffer;
				buffer++;
				count++;
				char* re =(char*)realloc(str,sizeof(char)*count);
				if(re != NULL)
					tempaddress = re;
				else
				{
					printf("error : cannot allocate memory");
					return NULL;
				}
			}
			*(tempaddress+count) = '\0';
			
			tempaddress = str;



			buffer+=genderoffset;
			
			count = 0 ;
			char* tempgender =(char*)malloc(sizeof(char));
			if(tempgender==NULL)
			{
				printf("error : ccannot allocate memory");
				return NULL;
			}
			str = tempgender;
			
			while(*buffer!='<')
			{
				*(tempgender+count) = *buffer;
				buffer++;
				count++;
				if(re != NULL)
					tempgender = re;
				else
				{
					printf("error : cannot allocate memory");
					return NULL;
				}
			}
			*(tempgender+count) = '\0';
			
			tempgender = str;


			
			struct_student* ptrtemp = (struct_student*)realloc(ptr,sizeof(struct_student)*(tot+1));
			if(ptrtemp != NULL)
				ptr = ptrtemp;
			else{
				printf("error: cannot allocate memory");
				return NULL;
			}
			
			(ptr+tot)->name = (char*)malloc(sizeof(char)*str_len(tempname));
			str_cpy((ptr+tot)->name,tempname);
			(ptr+tot)->address = (char*)malloc(sizeof(char)*str_len(tempaddress));
			str_cpy((ptr+tot)->address,tempaddress);
			(ptr+tot)->gender = (char*)malloc(sizeof(char)*str_len(tempgender));
			str_cpy((ptr+tot)->gender,tempgender);
			(ptr+tot)->id = atoi(tempid);
			(ptr+tot)->age = atoi(tempage);
		tot++;	// incrementing number of students var
		}
		buffer++; n//next char
		
	}
	
	
	*ftot =tot; // assigning final value of total
	stu_ptr = ptr;
	return ptr;

}

/*sort by name fn*/
struct_student* name_sort(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	char order ;
	printf("\nenter the order to sort the records by name 'a' - ascending 'd' - descending\n");
	do
	{
		getchar();
		scanf("%c",&order);
		if(order =='a' ||order=='d')
			break;
		else
			printf("invalid character please enter again ");
	
	}while(1);
	
	for(int itr1 = 0 ; itr1 < tot-1 ;itr1++)
	{
	//	printf("in sort name bef bef bef A");
		for(int itr2 = itr1+1 ; itr2 < tot ; itr2++)
		{	
	//		printf("in sort name bef bef A");
			if(str_cmp((stu_ptr+itr1)->name,(stu_ptr+itr2)->name)>0) //condition for ascending
			{
	//			printf("in sort name bef A");
				if(order == 'a') //acending order
				{
	//				printf("in sort name A");
					struct_student temp = *(stu_ptr+itr1);
					*(stu_ptr+itr1) = *(stu_ptr+itr2);
					*(stu_ptr+itr2) = temp;	//	swap_records(itr1,itr2);
				}
			}
			else if(str_cmp((stu_ptr+itr1)->name,(stu_ptr+itr2)->name)<0) //condition for descending
			{
				if(order == 'd') //desccending order
				{
					struct_student temp = *(stu_ptr+itr1);
					*(stu_ptr+itr1) = *(stu_ptr+itr2);
					*(stu_ptr+itr2) = temp;	//	swap_records(itr1,itr2);
				}
			}
		}
	}
	return stu_ptr;
}

/*sort by id fn*/
struct_student* id_sort(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	char order ;
	printf("\nenter the order to sort the records by name 'a' - ascending 'd' - descending\n");
	do
	{
		getchar();
		scanf("%c",&order);
		if(order =='a' ||order=='d')
			break;
		else
			printf("invalid character please enter again ");
	
	}while(1);
	
	for(int itr1 = 0 ; itr1 < tot-1 ;itr1++)
	{

		for(int itr2 = itr1+1 ; itr2 < tot ; itr2++)
		{	

			if((stu_ptr+itr1)->id>(stu_ptr+itr2)->id) //condition for ascending
			{

				if(order == 'a') //acending order
				{

					struct_student temp = *(stu_ptr+itr1);
					*(stu_ptr+itr1) = *(stu_ptr+itr2);
					*(stu_ptr+itr2) = temp;	//	swap_records(itr1,itr2);
				}
			}
			else if((stu_ptr+itr1)->id<(stu_ptr+itr2)->id) //condition for descending
			{
				if(order == 'd') //desccending order
				{
					struct_student temp = *(stu_ptr+itr1);
					*(stu_ptr+itr1) = *(stu_ptr+itr2);
					*(stu_ptr+itr2) = temp;	//	swap_records(itr1,itr2);
				}
			}
		}
	}
	return stu_ptr;
}

/*function to display individual records*/
void display_rec(struct_student* st)
{
	printf("\nNAME    : %s",st->name);
	printf("\nID      : %d",st->id);
	printf("\nADDRESS : %s",st->address);
	printf("\nGENDER  : %s",st->gender);
	printf("\nAGE     : %d",st->age);
	
}


/*display fn to display entire db*/
void display(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	for(int itr = 0 ; itr < tot ; itr++)
	{
		display_rec(stu_ptr+itr);
	}
}


/*fn to search for a name and display*/
void name_search(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	printf("enter the name to search\n");
	char* queryname;
	scanf("%s",queryname);
	int found = 0;
	for(int itr = 0 ; itr < tot ; itr++)
	{
		if((str_cmp((stu_ptr+itr)->name,queryname))==0)
		{
			found = 1;
			display_rec(stu_ptr+itr);
		}
		
	}
	if(found == 0)
		printf("record not found\n");

}

/*fn to search for a id and display*/
void id_search(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	printf("enter the id to search\n");
	int queryid;
	scanf("%d",&queryid);
	int found = 0 ;
	for(int itr = 0 ; itr < tot ; itr++)
	{
		if((stu_ptr+itr)->id == queryid)
		{
			found = 1;
			display_rec(stu_ptr+itr);
		}
		
	}
	if(found == 0)
		printf("record not found");
	
}



/*function to add records to DB*/
struct_student* addrecords(stu_ptr,tot)
struct_student* stu_ptr;
int* tot;
{
	printf("\n enter the number of students \n ");
	int newtot ;
	scanf("%d",&newtot);
	int i =*tot;
	*tot = *tot + newtot;
	struct_student* temptr = (struct_student*)realloc(stu_ptr,(*tot)*sizeof(struct_student));
	if(temptr ==NULL)
	{
		return NULL;
	}
	else
	{
		stu_ptr = temptr;
		
	}
	
	for(; i < (*tot) ; i++)
	{
		(stu_ptr+i)->id = uniqid++;
		printf(" \n enter the name of student :");
		(stu_ptr+i)->name = get_string();
		
		printf(" \n enter the age of student :");
		(stu_ptr+i)->age = get_age();
		
		printf(" \n enter the address :");
		(stu_ptr+i)->address = get_string();
		
		printf(" \n enter the gender(m/f) :");
		(stu_ptr+i)->gender = get_gender();
	}
	
	return stu_ptr;
}

/* function to free memory*/
int freemem(stu_ptr,tot)
struct_student* stu_ptr;
int tot;
{
	for(int itr = 0 ; itr < tot ;itr++)
	{
		if((stu_ptr+itr)!= NULL)
		{
			if((stu_ptr+itr)->name!=NULL)
				free((stu_ptr+itr)->name);
			else
				return -1;
			if((stu_ptr+itr)->address!=NULL)
				free((stu_ptr+itr)->address);
			else
				return -1;
			
			free(stu_ptr+itr);
		}
		else
			return -1;
		
	}
	
}

struct_student* delete(stu_ptr,tot)
struct_student* stu_ptr;
int* tot;
{
	printf("enter 1 for entering name of the record to be deleted or enter 2 if you know the id of the record...\n");
	int c;
	scanf("%d",&c);
	char* delname;
	int delid;
	if(c == 1)
	{
		printf("enter name\n");
		scanf("%s",delname);
	}
	else
	{
		printf("enter id\n");
		scanf("%d",&delid);
	}
	int found = 0 ;
	for(int itr = 0 ; itr < *tot ; itr++)
	{
		if(c==1)
		{
			if(strcmp((stu_ptr+itr)->name,delname)==0)
			{
				found = 1;
				memmove((stu_ptr+itr),(stu_ptr+itr+1),((*tot)-itr-1)*sizeof(struct_student));
				(*tot)--;
				break;
			}
		}
		else
		{
			if((stu_ptr+itr)->id == delid)
			{
				found = 1;
				memmove((stu_ptr+itr),(stu_ptr+itr+1),((*tot)-itr-1)*sizeof(struct_student));
				(*tot)--;
				break;
			}
		}
		
	}
	if(found == 0)
		printf("record not found");
	else
		printf("record deleted successfully");
}


/*main*/
void main()
{
	struct_student* stu_ptr;
	int tot ;
	FILE* fp;
	printf("_____________STUDENT DATA-BASE____________\n");
	
	int init;
	printf("press 1 to access the DataBase / press 2 to create new DataBase\n"); 
	
	scanf("%d",&init);
	
	if(init == 2)  //option to create new DB
	{
		printf("warning : the existing database will be deleted...press 2 to continue 1 to exit \n");
		scanf("%d",&init);
		if(init != 2)
			return;
			
		printf("\n enter the number of students \n ");

		scanf("%d",&tot);
	
		stu_ptr = (struct_student*)malloc(tot*sizeof(struct_student));	//allocating memory for student ptr initally one structure bytes
		if(stu_ptr ==NULL)
		{
			printf("error: cannot allocate memory");
			return;
		}
	
		for(int i = 0 ; i < tot ; i++)
		{
			(stu_ptr+i)->id = uniqid++;	//assign id and increment
			
			/*using getter functions for remaining data*/			
			printf(" \n enter the name of student %d :",i+1);
			(stu_ptr+i)->name = get_string();
			
			printf(" \n enter the age of student :");
			(stu_ptr+i)->age = get_age();
			
			printf(" \n enter the address :");
			(stu_ptr+i)->address = get_string();
				
			printf(" \n enter the gender(m/f) :");
			(stu_ptr+i)->gender = get_gender();
		}
		
		int struct_size = sizeof(stu_ptr);
	
		fp = fopen("data.txt","wb+");
		if(fp == NULL)
			 return;
			
	
		
	}
	else if(init ==1)
	{

		fp = fopen("data.txt","rb+"); //opening in read mode to copy data from file to buffer
		if(fp == NULL)
			return;
		stu_ptr = readfrom(stu_ptr,&tot,fp);
		
		if(fp!= NULL)
			fclose(fp);
		fp = fopen("data.txt","wb+");  //opening again in write mode to write buffer to file at the end
		
		uniqid = ((stu_ptr+tot)->id + 1); //updating the id value for new records to be added 
		
	}
		
	int ch = 0;
	do{
		
		printf("\n\n\n \t\tMENU: \n\n\n");
		printf("press 1 to sort by name \n");
		printf("press 2 to sort by id \n");
		printf("press 3 to search by name \n");
		printf("press 4 to search by id \n");
		printf("press 5 to view the records \n");
		printf("press 6 to add new records \n");
		printf("press 7 to delete a records \n");
		printf("press 0 to exit \n");
		
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
			{
				stu_ptr = name_sort(stu_ptr,tot);
				
				break;
			}
		
			case 2:
			{
				stu_ptr = id_sort(stu_ptr,tot);
				break;
			}
			case 3:
			{
				name_search(stu_ptr,tot);
				break;
			}
			case 4:
			{
				id_search(stu_ptr,tot);
				break;
			}
			case 5:
			{
				display(stu_ptr,tot);
				break;
			}
			
			case 6:
			{
				stu_ptr = addrecords(stu_ptr,&tot);
				break;
			}
			
			case 7:
			{
				delete(stu_ptr,&tot);
				break;
			}
			
			case 0:
			{

				writeto(stu_ptr,tot,fp);
				if(fp!=NULL)
					fclose(fp);
				freemem(stu_ptr,tot);
				break;
			}
		
			default:
				printf("enter valid choice");
		}
	}while(ch!=0);

}



