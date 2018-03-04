#include"stdio.h"
#include"stdlib.h"
#include"string.h"
void main(){
	int i = 1;
	char* str = (char*)malloc(sizeof(char));
	printf("enter a paragraph and press '~' to mark the end");
	int word = 1;
	while((str[i-1] = getchar())!='~')
	{	
		if(str[i-1]==' ')
			word++;
		i++;
		str = (char*)realloc(str,i*sizeof(char));
	}
	str[i] = '\0';
	printf("\n\n%s",str);
	printf("\n\n%d",word);
	while(getchar()!='\n')
		;
	char** arr =(char**) malloc(word*(sizeof(char*)));
	if(arr == NULL)
		printf("error");
	int k = 0;
			char* t = (char*)malloc(sizeof(char)); // character array to store a single word

	for(int i = 0 ; i < word ; i++){
				int j = 0;

		while((t[j]=str[k])!=' '&&(t[j]=str[k])!='~')
		{
			j++;
			k++;
			t = (char*)realloc(t,j*sizeof(char));
			
		}
				t[j] = '\0';		

		k++;
		arr[i] =(char*)malloc(j*sizeof(char));
		strcpy(arr[i],t);
		t = (char*)realloc(t,sizeof(char));


	}
	printf("enter the word to delete\n");
	char checkword[20];
	scanf("%s",checkword);
	for(int i = 0 ; i < word ; i++){
		if(strcmp(arr[i],checkword)==0){
			arr[i] =(char*)realloc(arr[i],sizeof(char));
			strcpy(arr[i],"\0");
			continue;
			
		
		}
		char reword[20];
		strcpy(reword,checkword);
		char checkword2[20];
		strcpy(checkword2,checkword);
		strcat(checkword2,",");
		if(strcmp(arr[i],checkword2)==0){
			arr[i] =(char*)realloc(arr[i],sizeof(char));
			strcpy(arr[i],",");
			continue;
		}
				strcat(reword,".");

		if(strcmp(arr[i],reword)==0){
			arr[i] =(char*)realloc(arr[i],sizeof(char));
			strcpy(arr[i],".");
			continue;
		}
		//printf("%s ",arr[i]);
	}
	for(int i = 0 ; i < word ; i++){
		printf("%s ",arr[i]);
	}
}