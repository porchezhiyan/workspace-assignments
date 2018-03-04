

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct  student{ //student structure
	
        int id;

	char name[25];
	char dob[10];
	char addr[300];
	char gender[8];

}struct_student;	//typedef to STUENT

struct_student* student_arr; // array of stduent structure

int student_count = 0; //size of database at any instant


// display student data at ith index
void display_rec(i)
int i;
{
//	printf("\n\t details of the student searched are...\t\n\n");
        printf("\n \t name    :\t %s ",student_arr[i].name); 
        printf("\n \t id      :\t %d ",student_arr[i].id);
        printf("\n \t address :\t %s ",student_arr[i].addr);       
        printf("\n \t gender  :\t %s ",student_arr[i].gender);  
        printf("\n \t DOB     :\t %s \n",student_arr[i].dob);


}


// display all student records 
void display_records(){
	for(int i = 0 ; i < student_count ; i++)
		display_rec(i);
}


// name search
void namesearch()
{
	char query_name[25];
	printf("\nenter the name of the student to search\n");
	scanf("%s",query_name);
	printf("the name to be searched is : %s ,",query_name);
	if(student_count == 0)
	{
		printf("\nthe data base is empty\\n");
	}
	else
	{	
		int found = 0 ;
		for(int i = 0 ; i < student_count ; i++)
		{
			if(strcmp(student_arr[i].name,query_name)==0)
			{
				found = 1;
				printf("\n  the record is found at position %d\n ",i+1);
			        printf("\n\t details of the student searched are...\t\n\n");

				display_rec(i);
				break;
				
			}
		}             
		if(!found) 
                {
                        printf("\nthe name you enter does not match with any records \n");
                }

		
	}
	
}



// id search
void idsearch()
{
        int query_id;
        printf("\nenter the id of the student to search\n");
        scanf("%d",&query_id);
        if(student_count == 0)
        {
                printf("\nthe data base is empty\\n");
        }
        else
        {
		int found = 0;
                for(int i = 0 ; i < student_count ; i++)
                {
                        if(student_arr[i].id==query_id)
                        {
				found = 1;
                                printf("\n  the record is found at position %d\n ",i+1);
                                display_rec(i);
				break;

                        }
                }
		if(!found)
		{
			printf("\nthe id you enter does not match with any records \n");
		}

        }
}

//swap records
void swap_records(int i , int j)
{
	struct_student student_temp ;  // holds the adress of first record
	
	//copy first to temp
        strcpy(student_temp.name,student_arr[j].name);
        strcpy(student_temp.addr,student_arr[j].name);
        strcpy(student_temp.dob,student_arr[j].name);
        student_temp.id = student_arr[j].id;
	strcpy(student_temp.gender,student_arr[j].gender);
	
	// copy second to first
	strcpy(student_arr[j].name,student_arr[i].name);
        strcpy(student_arr[j].addr,student_arr[i].name);                
        strcpy(student_arr[j].dob,student_arr[i].name);                
        student_arr[j].id = student_arr[i].id;
        strcpy(student_arr[j].gender,student_arr[i].gender);

	// copy temp to second
	strcpy(student_arr[i].name,student_temp.name);
        strcpy(student_arr[i].addr,student_temp.name);                
        strcpy(student_arr[i].dob,student_temp.name);                
	student_arr[i].id = student_temp.id;
	strcpy(student_arr[i].gender,student_temp.gender);
       
}



char order = 0;	// represents the order of sorting 



//name sort 
void namesort()
{
	for(int i = 0 ; i < student_count ;i++)
	{
		for(int j = i+1 ; j < student_count ; j++)
		{
			
			
			if(strcmp(student_arr[i].name,student_arr[j].name)>0) //condition for ascending
			{
				if(order == 'a') //acending order
					swap_records(i,j);
			}
			else if(strcmp(student_arr[i].name,student_arr[j].name)<0) // condition for descending
			{
				printf("\n%s less tan %s\n",student_arr[i].name,student_arr[j].name);
				if(order == 'd')  // descending order
					swap_records(i,j);
			}
		}
	}
	char ordertoprint[4];
	if(order =='a')
		strcpy(ordertoprint,"as");
	else
		strcpy(ordertoprint,"des");
	printf(" records after sorting in %scending order of the name... \n \n",ordertoprint);
	
	display_records();
}



//name sort 
void idsort()
{
        for(int i = 0 ; i < student_count ;i++)
        {
                for(int j = i+1 ; j < student_count ; j++)
                {


                        if(student_arr[i].id>student_arr[j].id) //condition for ascending
                        {
                                if(order == 'a') //acending order
                                        swap_records(i,j);
                        }
                        else if(student_arr[i].id<student_arr[j].id) // condition for descending
                        {
                                if(order == 'd')  // descending order
                                        swap_records(i,j);
                        }
                }
        }
        
	char ordertoprint[4];
	if(order =='a')
		strcpy(ordertoprint,"as");
	else
		strcpy(ordertoprint,"des");
	printf(" records after sorting in %scending order of the id... \n \n",ordertoprint);
	
	display_records();
}



int temp_id = 0; //to auto generate ID ; 0 for intial record 



/* delete record by id */
void delete_record_i(int delete_id)
{
	
        if(student_count == 0)
        {
                printf("\nthe data base is empty\n");
        }
        else
        {
                int found = -1;
                for(int i = 0 ; i < student_count ; i++)
                {
                        if(student_arr[i].id==delete_id)
                        {
                                found = i;
                                printf("\n  the record to be delted is  \n "); // finding the position of record that needs to be deleted

                                display_rec(i);
                                break;

                        }
                }
		if(found!=-1)
		{
			for(int i = found ; i < student_count-1 ; i++)
			{
				student_arr[i].id = student_arr[i+1].id ;
				strcpy(student_arr[i].name,student_arr[i+1].name);
	            		strcpy(student_arr[i].gender,student_arr[i+1].name);
		                strcpy(student_arr[i].addr,student_arr[i+1].name);
			        strcpy(student_arr[i].dob,student_arr[i+1].dob);
	
		
			} 
			student_count--; //reducing the count as a record is deleted
			student_arr = (struct_student*)realloc(student_arr,sizeof(struct_student)*student_count);        //reallocating memory 
		
			printf("the record deleted successfully\n");
		}
                else
                {
                        printf("\nthe id you enter does not match with any records \n");
                }

        }

}



/* delete record by name */
void delete_record_n(char* search_name)
{

        if(student_count == 0)
        {
                printf("\nthe data base is empty\n");
        }
        else
        {
                int found = -1;
	                for(int i = 0 ; i < student_count ; i++)
                {
                        if(strcmp(student_arr[i].name,search_name)==0)
                        {
                                found = i;
                                printf("\n  the record to be delted is  \n "); // finding the position of record that needs to be deleted

                                display_rec(i);
                                break;

                        }
                }
                if(found!=-1)
                {
                        for(int i = found ; i < student_count-1 ; i++)
                        {
                                student_arr[i].id = student_arr[i+1].id ;
                                strcpy(student_arr[i].name,student_arr[i+1].name);
                                strcpy(student_arr[i].gender,student_arr[i+1].name);
                                strcpy(student_arr[i].addr,student_arr[i+1].name);
                                strcpy(student_arr[i].dob,student_arr[i+1].dob);


                        } 
                        student_count--; //reducing the count as a record is deleted
                        student_arr = (struct_student*)realloc(student_arr,sizeof(struct_student)*student_count);        //reallocating memory 
			printf("the record deleted successfully...\n");
                }
                else
                {
                        printf("\nthe name you enter does not match with any records \n");
                }

        }

}


// main function


void main()
{
	student_count = 0;

	printf("\n enter the number of students \n ");

	scanf("%d",&student_count);   // getting the number of students

	student_arr = (struct_student *)malloc(student_count*sizeof(struct_student));
	if(student_arr == NULL)
		printf("error : cannot allocate memory \n");
	printf("no of students : %d",student_count);
	for(int i = 0 ; i < student_count ;i++)
	{

		/* declaration of temporary variables */
		char temp_name[25];
		
		char temp_DOB[10];
		char temp_addr[300];
		char temp_gender;
		
		/* getting values from user */
		printf(" \n enter the name of student %d :",i+1);
		scanf("%s",temp_name);
		//printf(" \n enter the student id  :"); 
		//		scanf("%d",&temp_id);
		temp_id++;
		printf(" \n enter the address :"); 
		scanf("%s",temp_addr);  
		while(getchar()!='\n')
			;
		printf(" \n enter the gender ('F'/'M'): "); 
				
		scanf("%c",&temp_gender);
				

		while(1)
		{
			if((temp_gender =='M')||(temp_gender =='m')||(temp_gender =='F')||(temp_gender =='f')){
				break;
			}
			else
			{
				while((getchar())!='\n')
					;
				printf("not a valid character ");
				printf(" \n enter the gender ('F'/'M'): "); 
				scanf("%c",&temp_gender);
				continue;
			}
			break;
		}
		printf(" \n enter the Date of Birth (dd-mm-yyyy) :"); 
		scanf("%s",temp_DOB);

		/* storing varoables in structure */
		student_arr[i].id = temp_id;
		strcpy(student_arr[i].name,temp_name);
		strcpy(student_arr[i].addr,temp_addr);
		strcpy(student_arr[i].dob,temp_DOB);
		if(temp_gender == 'f' || temp_gender =='F')
			strcpy(student_arr[i].gender,"Female\0");
		if(temp_gender == 'm' || temp_gender =='M')
			strcpy(student_arr[i].gender,"Male\0");
       	
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
				while(getchar()!='\n'){
					;
				}
				do  
				{
					printf("\npress 'a' for ascending  / 'd' for descending\n");					
					char sort_opt;
					scanf("%c",&sort_opt);
					if(sort_opt=='a'||sort_opt=='d')
					{
						order = sort_opt;
						namesort();
						break;
					}
					else{
						printf("please enter a valid sorting option\n");		
						while(getchar()!='\n'){
							;
						}
					}
				}while(1);
				break;
			}

			case 2:
			{       
				while(getchar()!='\n'){
					;
				}
				do  
				{
						
					printf("\npress 'a' for ascending  / 'd' for descending\n ");
	
					char sort_opt;
					scanf("%c",&sort_opt);
					if(sort_opt=='a'||sort_opt=='d')
					{
						order = sort_opt;
						idsort();

						break;
					}
					else{
						printf("please enter a valid sorting option\n");
						while(getchar()!='\n'){
						}
					}
				}while(1);
				break;
			}
	
			case 3:
				namesearch();
				break;
			case 4:
				idsearch();
				break;
			case 5:
				printf(" students data : \n\n ");
				display_records();
				break;
			case 6:
			{
				int n1 ;
				printf("\n enter the number of records to create \n ");
				scanf("%d",&n1);
				int i = student_count;
				student_count += n1; 
				student_arr = (struct_student *)realloc(student_arr,student_count*sizeof(struct_student));
				if(student_arr == NULL){
					printf("error : out of memory");
					exit(0);
				}
				for(;i<student_count;i++)
				{
					
					/* declaration of temporary variables */
					char temp_name[25];
					
					char temp_DOB[10];
					char temp_addr[300];
					char temp_gender;
					
					/* getting values from user */
					printf(" \n enter the name of student %d :",i+1);
					scanf("%s",temp_name);
					//printf(" \n enter the student id  :"); 
					//		scanf("%d",&temp_id);
					temp_id++;
					printf(" \n enter the address :"); 
					scanf("%s",temp_addr);  
					while(getchar()!='\n')
						;
					printf(" \n enter the gender ('F'/'M'): "); 
							
					scanf("%c",&temp_gender);
							

					while(1)
					{
						if((temp_gender =='M')||(temp_gender =='m')||(temp_gender =='F')||(temp_gender =='f')){
							break;
						}
						else
						{
							while((getchar())!='\n')
								;
							printf("not a valid character ");
							printf(" \n enter the gender ('F'/'M'): "); 
							scanf("%c",&temp_gender);
							continue;
						}
						break;
					}
					printf(" \n enter the Date of Birth (dd-mm-yyyy) :"); 
					scanf("%s",temp_DOB);

					/* storing varoables in structure */
					student_arr[i].id = temp_id;
					strcpy(student_arr[i].name,temp_name);
					strcpy(student_arr[i].addr,temp_addr);
					strcpy(student_arr[i].dob,temp_DOB);
					if(temp_gender == 'f' || temp_gender =='F')
						strcpy(student_arr[i].gender,"Female\0");
					if(temp_gender == 'm' || temp_gender =='M')
						strcpy(student_arr[i].gender,"Male\0");

					
				}
			}
			break;
			
			case 7:
			{
				char basis; //delte by id or name
				while(getchar()!='\n')
					;
				printf("\npress 'i' to deletre record by id & 'n' to delete record with name\n");

				printf("%d",scanf("%c",&basis)); //
				
				printf("\n %c",basis);
				while(1)
				{
					if(basis != 'n'&& basis != 'N' && basis !='i' && basis !='I')
					{	
						while(getchar()!='\n')
							;
						printf("enter valid character ");
						scanf("%c",&basis);
						continue;
					}
						break;
					
				}

				if(basis=='i'||basis=='I')
				{
					int id;
					printf("\nenter the id of the record to be deleted\n");
					scanf("%d",&id);
					delete_record_i(id);
				}
			        if(basis=='n'||basis=='N')
                                {
                                        char name[20];
                                        printf("\nenter the name of the record to be deleted\n");
                                        scanf("%s",name);
                                        delete_record_n(name);
                                }
			}

			case 0:
				break;
		
			default :
				printf("enter valid input \n");
		}
		

	}while(ch!=0);


}

