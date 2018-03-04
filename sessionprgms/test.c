#include"stdio.h"
#include"utils.h"
#include"string.h"

int substr_rep(char* str,char* str2,char* str3)
{
		printf("\n in function :%s %s %s",str,str2,str3);
	//int diff;
	//diff = (str_len(str2)>str_len(str3)) ? (str_len(str2)-str_len(str3)) : str_len(str)-str_len(str3) ;
	for(int i = 0 ; i < str_len(str) ; i++)
	{	int t = i; //store start index of matching pattern
		int j;
		int flag = 0 ;
		for( j = 0 ; j < str_len(str2) ;j++,i++)
		{
			//printf("   \n%c    %c   %d",str1[i],str2[j],j);
			if(str[i] != str2[j])
			{
				flag = 1;
				break;
			}	
		}
		if(flag == 0)
		{
			/* i will have start index of remaining text*/
			printf("%d",str_len(str3));			
//			str[1]=str3[0];
//			str[2]=str3[1];
		//	printf("%c %c",str[2],str3[1]);			

									
			for(int k = 0 ; k < str_len(str3) && t < str_len(str);k++,t++)
				str[t] = str3[0];
			//printf("%d %d",t,i);
			
			int count = 0;
			j = i;
			while(str[i]!='\0')
			{
				i++;
				count++;
			}
			printf("   t+1 == %c j+1==%c ",str[t+1],str3[j+1]);			
			memmove(str+t,str+j,count+1);
		}
	}
	printf("\n in function :%s %s %s",str,str2,str3);
	
}
void main()
{
	char* a, b, c;
	char s[20],t[10],v[10];
	strcpy(s,"apple");
	strcpy(t,"ppl");
	strcpy(v,"tt");
	substr_rep(s,t,v);
}
	
	
	
	
	
	
