/* 22/2 6:12p */
#include"stdio.h"
#include"stdlib.h"



//user defined function for string compare
int str_cmp(char* str1, char* str2)
{
        for(;*str1==*str2;str1++,str2++)
        {
                if(*str1=='\0' && *str2=='\0')
                        return 0;
        }
                return (*str1 - *str2);
}


// userdefined function copy string from secong arg to first
void  str_cpy(char* str1, char* str2)
{
        int i = 0;
        while((str1[i]=str2[i])!='\0')
                i++;
}

// function that returns the length of the string
int str_len(const char* str1) 
{
	int i = 0 ;
	while(str1[i]!='\0')
		i++;
	return i;
}

// returns 1 if str2 is substring str1 else returns 0;

int str_str(char* str1,char* str2)
{	
	if(str_cmp(str1,str2)==0)
		return 1;
		
	if(str_len(str2)>str_len(str1))
		return 0;
	for(int i = 0 ; i < str_len(str1) ; i++)
	{	int t = i; //store i value to restore at end
		int j;
		for( j = 0 ; j < str_len(str2) ;j++)
		{
			//printf("   \n%c    %c   %d",str1[i],str2[j],j);
			if(str1[i] != str2[j])
				break;
			i++;
				
		}
		i = t;
		if(j==(str_len(str2)))
			return 1;
	}
	
	
}



//to upper case
char* str_upr(const char* string)
{
	char* out = (char*) malloc(sizeof(char)*str_len(string));
	
//	printf("%sin strupr \n",string);
	*out = *string;
	int i = 0;
	while((*string)!='\0')
	{
		if((*string)>96&&(*string)<122)
			*(out+i)=(*string)-32;
		else
			*(out+i)=(*string);
		string++;
		i++;
	}
	//printf("%s\n out strupr",string);
	return out;
}



// string compare ignore case
int str_cmpi(char* const str1,const  char* str2)
{
	char* temp1 = str_upr(str1);
	char* temp2 = str_upr(str2);
	return str_cmp(temp1,temp2);
}


//user defined fn for strcat
char* str_cat(char* str1, char* str2)
{

	char* base =(char*) malloc(str_len(str1)+str_len(str2));
	char* str3 = base;
	int i = str_len(str1);
        while((*str3=*str1)!='\0')
	{	
        	str1++;
        	str3++;
        }
        
        while((*str3=*str2)!='\0')
	{	
        	str2++;
        	str3++;
        }
        return base;
}

//convert digit(0-9) value to char eg : 1 -> '1'
char dtoc(int a)
{
	if(a >= 0 && a <= 9)
	{
		return ('0'+a);
	}
	else
		return '\0';
}

int reverseint(int a)
{
	int out = 0;	
	while(a>0)
	{
		int temp = a%10;
		a = a/10;
		out = out*10+temp;
	}
	return out;
}

/*reverse string*/
char* str_rev(char* str)
{
	char* rts = (char*)malloc(str_len(str)*sizeof(char));
	int c = 0;
	char* base = rts;
	
	while(*(str)!='\0')
	{
		str++;
		c++;
	}
	str--;
	while(c>0)
	{
		//printf("%c",*str);
		c--;
		*rts = *str;
		str--;
		rts++;
	}
	rts = '\0';
	
	return base;	
	
}




/*convert integer to string eg : 25 -> "25"*/
char* itos(int a)
{
	int temp = a;
	int c = 0;
	while(temp>0)
	{
		temp=temp/10;
		c++;
	}
	char* out = (char*)malloc(c*sizeof(char));
	char* base = out;
	while(a>0)
	{
		temp = a%10;
		a = a/10;
		(*out++) = dtoc(temp);
	}
	*out = '\0';
	return str_rev(base);
}


int is_digit(char c)
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}

int ctod(char c)
{
	if(c >= '0'&& c <= '9')
		return(c - '0');
	else
		return -1;
}

int stoi(char* str)
{
	int sum = 0;
	while(*str!='\0')
	{
		
		int a = ctod(*str);
		sum = sum*10 + a;
		str++;
	}
	return sum;
	
}

int is_alpha(char c)
{
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
	{
		return 1;
	}
	else
		return 0;
}



