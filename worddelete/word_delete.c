#include"stdio.h"
#include"stdlib.h"
#include"utils.h"
#include"string.h"

int ignore_case = 1;
#define string_end  '\0'

/* to replace the  str2 argument present as a subword in str with str3 */
int substr_rep(char* str,char* str2,char* str3) //function replace substring
{
	
	for(int counter = 0 ; counter < str_len(str) ; counter++) //iterate till lentgh of str 
	{	int start = counter; //store start index of matching pattern
		int itr2;
		int flag = 0 ; //to indicate the presence of subword
		for( itr2 = 0 ; itr2 < str_len(str2) ;itr2++,counter++) //iterate till end of search word 
		{
			if(ignore_case == 1) //case insensitive search 
			{		
				if(charupr(str[counter]) != charupr(str2[itr2])) //no subword ; search in common upper case
				{
					flag = 1;//indiacte not a  subword
					counter = start; // restore counter to original value
					break;
				}	
			}
			else	//case sensitive search
			{
				if(str[counter] != str2[itr2]) //no subword 
				{
					flag = 1;//indiacte not a  subword
					counter = start; // restore counter to original value
					break;
				}
			}
		}
		if(flag == 0)
		{					
			if(str_len(str2)>=str_len(str3))	// when search word is smaller than the word to be replaced
			{
				for(int itr3 = 0 ; itr3 < str_len(str3) && start < str_len(str);itr3++,start++) //iterate till length of string 3
					str[start] = str3[itr3];	//assigning the replacment string to start
				
				int count = 0;
				itr2 = counter;
				while(str[counter]!=string_end)
				{
					counter++;
					count++;
				}

				memmove(str+start,str+itr2,count+1);
			}
			else
			{
				str = (char*) realloc(str,str_len(str)+1);
				memcpy(str+start,str3,str_len(str3));
			}
		}
	}
	
}

void main(){
	
	int iterator = 1; // to iterate and store number of characters
	

	char* str = (char*)malloc(iterator*sizeof(char));   //initally has size of single character
	
	printf("type a paragraph and press '~' and 'ENTER' to mark the end\n");
	
	int word = 1;  //minimum paragraph has single word
	
	while((str[iterator-1] = getchar())!='~') //gets character and sores in str repeatedly unless ~ and enter is pressed
	{	
		if(str[iterator-1]==' '||str[iterator-1]=='\n'||str[iterator-1]=='\t')  //condition to calculate number of words
			word++;
		iterator++;
		str = (char*)realloc(str,iterator*sizeof(char)); //allocates bytes for nxt characters
	}
	
	
	str[iterator] = string_end;//to mark the end of string
	
 
	printf("\n\nparagraph is : \n  %s",str);    //printing the input

	printf("\n\nthe number of words is: %d\n",word); //print num of words 

	while(getchar()!='\n')   //remove characters in buffer
		;
	char** arr =(char**) malloc((word+1)*(sizeof(char*)));   //create array of charctr  pointers
	if(arr == NULL){
		printf("\nerror:cant allocate memory\n");
		exit(0);
	}
			

			
	int k = 0; //iterator for paragraph
	
	char* t = (char*)malloc(sizeof(char)); // character array to store a single word

		//		printf("\nerror:cant allocate memory\n");

	for(int i = 0 ; i < word ; i++){
			
		int j = 1; //iterator and number of characters held

		while((t[j-1]=str[k])!=' '&&(t[j-1]=str[k])!='\n'&&(t[j-1]=str[k])!='\t'&&(t[j-1]=str[k])!='~')  //to check single word   //t[0]
		{
			j++;     
			k++;
			t = (char*)realloc(t,j*sizeof(char));      //t=2
//				printf("%s\n",t);
		}
		t[j-1] = string_end; //end of each word


		
		
		k++;//skip space
		
		arr[i] =(char*)malloc(sizeof(t)); // creating memory hold the word

		str_cpy(arr[i],t);// copy the word 
		t = (char*)realloc(t,sizeof(char));//reallocating t with single byte to start again

	//	printf("%s\n",t);
	}
	printf("\nenter the word to be replaced\n");
	char checkword[20];
	scanf("%s",checkword); // gets the word to be replaced
	printf("\nenter the replacement word\n");
	char repword[20];
	scanf("%s",repword);

//	for(int i = 0 ; i < word ; i++)
//		printf("%d\n",str_cmp(arr[i],checkword));

	
	int ch = 0;
	do
	{
		ch = 0;
		printf("\npress 1 for word replacement \n");
		printf("press 2 for sub-word replacement \n");
		printf("press 3 for case - sensitive word replacement \n");
		printf("press 4 for case - sensitive sub-word replacement \n");	
		printf("press 0 to exit \n");
		printf("\nenter your choice \n");
		scanf("%d",&ch);
		do
		{
			if(ch !=0 && ch!=1 && ch!=2 && ch!=3 &&ch!=4)
			{
				while(getchar()!='\n')
					;
				printf("invalid choice enter your choice again \n");
				scanf("%d",&ch);
			}
	
	
		}while(ch !=0 && ch!=1 && ch!=2 && ch!=3 &&ch!=4);
		switch(ch)
		{
			 case 1:
			 {
		 	
				for(int i = 0 ; i < word ; i++){
					if(str_cmp(arr[i],checkword)==0){
	
						arr[i] =(char*)realloc(arr[i],sizeof(repword)); ///allocates size of the replcmt word
						str_cpy(arr[i],repword);
						continue;
					}	
				}
			}
			break;
		
			case 2:
			{
				for(int i = 0 ; i < word ; i++){
					if(str_cmp(arr[i],checkword)==0)
					{
						arr[i] =(char*)realloc(arr[i],sizeof(repword)); ///allocates size of the replcmt word
						str_cpy(arr[i],repword);
						continue;
					}
				
				}
	
				for(int i = 0 ; i < word ; i++)
				{			
					if(str_str(arr[i],checkword))  // if check word is substring of a word in para
					{
						substr_rep(arr[i],checkword,repword);
					}
				}
			}
			break;
			
			
			case 3:
			 {
		 		ignore_case = 1;
				for(int i = 0 ; i < word ; i++){
					if(str_cmpi(arr[i],checkword)==0){
	
						arr[i] =(char*)realloc(arr[i],sizeof(repword)); ///allocates size of the replcmt word
						str_cpy(arr[i],repword);
						continue;
					}	
				}
			}
			break;
			
			case 4:
			{
		 		ignore_case = 1;
				for(int i = 0 ; i < word ; i++){
					if(str_cmpi(arr[i],checkword)==0)
					{
						arr[i] =(char*)realloc(arr[i],sizeof(repword)); ///allocates size of the replcmt word
						str_cpy(arr[i],repword);
						continue;
					}
				
				}
	
				for(int i = 0 ; i < word ; i++)
				{			
					if(str_str(arr[i],checkword))  // if check word is substring of a word in para
					{
						substr_rep(arr[i],checkword,repword);
					}
				}
			}
			break;
			
		
			case 0:
				break;
		
		
			default:
				printf("invalid choice");
		}

		printf("the paragraph is :\n");
		if(ch!=0)
		{
			for(int i = 0 ; i < word ; i++)
        	 	printf("%s ",arr[i]);
       		}
       		printf("\nenter the word to be replaced\n");
		char checkword[20];
		scanf("%s",checkword); // gets the word to be replaced
		printf("\nenter the replacement word\n");
		char repword[20];
		scanf("%s",repword);
       	}while(ch!=0);





}
