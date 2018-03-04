#include"stdio.h"
#include"utils.h"
#include"string.h"
#include"stdlib.h"
typedef struct  student{ //student structure
	
        int id;

	char *name;
	int age;
	char *address;
	char *gender;

}struct_student;	//typedef to STUENT



void main()
{
	int tot = 0;
	char* buffer ="<student><name>family</name><age>12</age><id>1</id><address>Qqwe</address><gender>male</gender></student><student><name>girl</name><age>9</age><id>22</id><address>aaaaaaaa</address><gender>female</gender></student>";
	char *basebuff = buffer;
	
	struct_student* ptr =NULL;
	while(*buffer != '\0')
	{
		if((*buffer) =='<' && *(buffer+1) =='s')
		{
			
			buffer+=15;
			
			int count = 0 ;
			char* str =(char*)malloc(sizeof(char));
			char* tempname = str;
			while(*buffer!='<')
			{
				*(tempname+count) = *buffer;
				buffer++;
				count++;
				tempname =(char*)realloc(str,sizeof(char)*count);
			}
			*(tempname+count) = '\0';
			
			tempname = str;
			
			
			printf("%s",str);	

			buffer+=12;
			
			count = 0 ;
			char* tempage =(char*)malloc(sizeof(char));
			str = tempage;
			
			while(*buffer!='<')
			{
				*(tempage+count) = *buffer;
				buffer++;
				count++;
				tempage =(char*)realloc(str,sizeof(char)*count);
			}
			*(tempage+count) = '\0';
			
			tempage = str;
			
			
			printf("age %s",str);
			
			
			buffer+=10;
			
			count = 0 ;
			char* tempid =(char*)malloc(sizeof(char));
			str = tempid;
			
			
			while(*buffer!='<')
			{
				*(tempid+count) = *buffer;
				buffer++;
				count++;
				tempid =(char*)realloc(str,sizeof(char)*count);
			}
			*(tempid+count) = '\0';
			
			tempid = str;
			
			
			printf("id %s",str);
			
			buffer+=14;
			
			count = 0 ;
			char* tempaddress =(char*)malloc(sizeof(char));
			str = tempaddress;
			
		//	printf("%c",*buffer);	
			
			while(*buffer!='<')
			{
				*(tempaddress+count) = *buffer;
				buffer++;
				count++;
				tempaddress =(char*)realloc(str,sizeof(char)*count);
			}
			*(tempaddress+count) = '\0';
			
			tempaddress = str;

			printf("address %s",str);
			
			buffer+=18;
			
			count = 0 ;
			char* tempgender =(char*)malloc(sizeof(char));
			str = tempgender;
			
			while(*buffer!='<')
			{
				*(tempgender+count) = *buffer;
				buffer++;
				count++;
				tempgender =(char*)realloc(str,sizeof(char)*count);
			}
			*(tempgender+count) = '\0';
			
			tempgender = str;
			
			
			printf("gender %s\n\n",str);
			
			ptr = (struct_student*)realloc(ptr,sizeof(struct_student)*(tot+1));
			
			(ptr+tot)->name = (char*)malloc(sizeof(char)*str_len(tempname));
			str_cpy((ptr+tot)->name,tempname);
			(ptr+tot)->address = (char*)malloc(sizeof(char)*str_len(tempaddress));
			str_cpy((ptr+tot)->address,tempaddress);
			(ptr+tot)->gender = (char*)malloc(sizeof(char)*str_len(tempgender));
			str_cpy((ptr+tot)->gender,tempgender);
			(ptr+tot)->id = atoi(tempid);
			(ptr+tot)->age = atoi(tempage);
		tot++;	
		}
		buffer++;
		
	}
	for(int i = 0 ; i < tot ; i++)
		printf("%s\n",(ptr+i)->name);
}
