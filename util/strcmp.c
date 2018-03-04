#include"stdio.h"
int str_cmp(char* str1, char* str2)
{
/*      int i = 0;
        while(str1[i]!='\0'&& str2[i]!='\0')
        {
                if(str1[i]!=str2[i])
                        return str1[i]-str2[i];
                i++;

        }
        if(str1[i]=='\0' && str2[i] == '\0')
                return 0;
        else if(str1[i]!='\0')
                return -1;
        else
                return 1;
*/
        for(;*str1==*str2;str1++,str2++)
        {
                if(str1=='\0')
                        return 0;
        }
        else
                return (str1 - str2);
}


// userdefined function copy string from secong arg to first
void  str_cpy(char* str1, char* str2)
{
        int i = 0;
        while((str1[i]=str2[i])!='\0')
                i++;
}


