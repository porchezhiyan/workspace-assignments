#include <stdio.h>                                                                                   
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define bit1 0
#define bit2 1
#define bit3 2

#pragma pack(push,1)
typedef struct{
   	 uint8_t signature[2];
   	 uint32_t filesize;
  	  uint32_t reserved;
 	  uint32_t offset_to_img;
} fileheader;

typedef struct{
    uint32_t dibheadersize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsperpixel;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t ypixelpermeter;
    uint32_t xpixelpermeter;
    uint32_t numcolorspallette;
    uint32_t mostimpcolor;
} bitmapinfoheader;

typedef struct {
    fileheader fh;
    bitmapinfoheader bmpih;
    
} bitmap;

#pragma pack(pop)

int padding;	//no of padding bits added
int Bytesperpixel;	//Bytesperpixel


typedef struct pixel
{
	unsigned char r;
	
	unsigned char g;
	
	unsigned char b;
}PIXEL;



/*rotate Anticlkwise 90' */
unsigned char* A_rotate(unsigned char* data , uint32_t* width , uint32_t* height,int* size)
{
	if(data == NULL ||*width < 1 ||*height < 1 || *size < 1)
	{
		printf("invalid input to rotate");
		return NULL;
	}

	int BPP = 3;		//bytes per pixel
	int lWidth = *width;	//local var for width & hyt
	int lHeight = *height;
	
	int imagedatasize = (lWidth*BPP*lHeight);  //size of actual data withut padding bytes
	
	unsigned char* imagedata = (unsigned char*)malloc(imagedatasize*sizeof(unsigned char));	//buffer to store data without padding bytes
	if(!imagedata )
	{
		printf("cannot allocate memory\n");
		return NULL;
	}
	
	unsigned char* temp_imagedata = imagedata; //pointer to store base address of data before padding
	unsigned char* temp_data = data;	//pointer to store base address of data with padding
	
	
	/*copying actual data from dat with padding bytes*/
	for(int itr = 0 ; itr < lHeight ; itr++)	//loop for every column
	{
		memcpy(imagedata,data,(lWidth*BPP-1));	//copy till actual width
		imagedata+=(lWidth*BPP);	//move to next row
		data +=(lWidth*BPP+padding);	//move to next row skipping padding bytes
	}
	
	imagedata = temp_imagedata; 	//reallocating base data
	data = temp_data;
	
	
	
	unsigned char* newimagedata = (unsigned char*)malloc(imagedatasize); //buffer to store rotated img data
	if(!newimagedata)
	{
		printf("error:cannot allocate memory");
		return NULL;
	}
	PIXEL* nid = (PIXEL*)(newimagedata);	//pixel pointers to handle RBG bytes
	PIXEL* id = (PIXEL*)(imagedata);

	
	for(int i = 0 ; i < lWidth;i++)
	{
		for(int j = 0 ; j < lHeight ;j++)
		{
			*(nid+j+(i*lHeight)) = *(id+lWidth-1+(lWidth*j)-i); //rotating each row one by one
		}
	}
	
	/*update new width and height	*/
	int temp = *width; 
	*width = *height;
	*height = temp;	
	
	
	
	int row_stride_length = (*width)*BPP;  //new stride length
	
	if((padding = row_stride_length % 4)==0) //if padding zero
		;
	else
	{
		padding = 4 - padding; //else number of bits added for padding
	}
		
	int newdatasize =  (*height)*((*width)*BPP+padding);//calculating total bytes of raw data nad padding bytes
	
	*size = newdatasize;//updating value for passed argument
    
    	unsigned char* newdata = (unsigned char*)calloc(1,newdatasize);
    	if(!newdata)
    	{
    		printf("memory allocation error");
    		return NULL;
    	}
	
	lWidth = *width;
	lHeight = *height;
	
	temp_imagedata = imagedata;
	temp_data = newdata;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(newdata,newimagedata,(lWidth*BPP-1));
		newimagedata+=(lWidth*BPP);
		newdata +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	newdata = temp_data;
	
	return (char*)newdata;
	
	if(data != NULL)
		free(data);
	
	if(data != NULL)
		free(newimagedata);
	
	if(data != NULL)
		free(imagedata);
}



/*HORIZONTAL FLIP...*/
int hflip(unsigned char* data , uint32_t* width , uint32_t* height,int size)
{
	int BPP = 3;
	int lWidth = *width;
	int lHeight = *height;
	
	int imagedatasize = (lWidth*BPP*lHeight);
	
	unsigned char* imagedata = (unsigned char*)malloc(imagedatasize*sizeof(unsigned char));
	
	unsigned char* temp_imagedata = imagedata;
	unsigned char* temp_data = data;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(imagedata,data,(lWidth*BPP-1));
		imagedata+=(lWidth*BPP);
		data +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	data = temp_data;
	
	if(data == NULL ||*width < 1 ||*height < 1 )
	{
		printf("invalid input to roate");
		return 0;
	}

	unsigned char* ndata = (unsigned char*)malloc(size);
	
	PIXEL* p = (PIXEL*)(imagedata);
	
	for(int c = 0 ; c < lHeight ; c++)
	{
		for(int r = 0 ; r < lWidth/2 ;r++)
		{
			
			PIXEL temp = *(p+r+(c*lWidth));
			*(p+r+(c*lWidth)) = *(p+(lWidth)-1-r+(c*lWidth));
			*(p+(lWidth)-1-r+(c*lWidth)) = temp;
			
		}	
	}
	
	temp_imagedata = imagedata;
	temp_data = data;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(data,imagedata,(lWidth*BPP-1));
		imagedata+=(lWidth*BPP);
		data +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	data = temp_data;
	
	
	return 1;
	
	
}

/*VERTICAL FLIP...*/
int vflip(unsigned char* data , uint32_t* width , uint32_t* height,int size)
{
	int BPP = 3;
	int lWidth = *width;
	int lHeight = *height;
	
	int imagedatasize = (lWidth*BPP*lHeight);
	
	unsigned char* imagedata = (unsigned char*)malloc(imagedatasize*sizeof(unsigned char));
	
	unsigned char* temp_imagedata = imagedata;
	unsigned char* temp_data = data;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(imagedata,data,(lWidth*BPP-1));
		imagedata+=(lWidth*BPP);
		data +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	data = temp_data;
	
	if(data == NULL ||*width < 1 ||*height < 1 )
	{
		printf("invalid input to roate");
		return 0;
	}
	
	int row_size = *width;
	int col_size = *height;
	
	unsigned char* ndata = (unsigned char*)malloc(size);
	
	PIXEL* p = (PIXEL*)(imagedata);

	
	
	printf("%d",row_size);
	
	for(int c = 0 ; c < lHeight/2 ; c++)
	{
		for(int r = 0 ; r < lWidth ;r++)
		{
			
			PIXEL temp = *(p+r+(c*lWidth));
			*(p+r+(c*lWidth)) = *(p+(lWidth*(lHeight-c-1))+r);
			*(p+(lWidth*(lHeight-c-1))+r) = temp;
			
		}	
	}
	
	temp_imagedata = imagedata;
	temp_data = data;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(data,imagedata,(lWidth*BPP-1));
		imagedata+=(lWidth*BPP);
		data +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	data = temp_data;
	
	
	return 1;
}

/*
PIXEL temp = *(p+r+(c*row_size));
			*(p+r+(c*row_size)) = *(p+((col_size-c-1)*row_size)+r);
			*(p+((col_size-c-1)*row_size)+r) = temp;
*/
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
	//getchar(); //eats new line
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


char* crop(unsigned char* data,int* width,int* height,int* size,int x,int y ,int newWidth ,int newHeight)
{
	if(data == NULL ||*width < 1 ||*height < 1 || *size < 1)
	{
		printf("invalid input to rotate");
		return NULL;
	}

	int BPP = 3;		//bytes per pixel
	int lWidth = *width;	//local var for width & hyt
	int lHeight = *height;
	
	int imagedatasize = (lWidth*BPP*lHeight);  //size of actual data withut padding bytes
	
	unsigned char* imagedata = (unsigned char*)malloc(imagedatasize*sizeof(unsigned char));	//buffer to store data without padding bytes
	if(!imagedata )
	{
		printf("cannot allocate memory\n");
		return NULL;
	}
	
	unsigned char* temp_imagedata = imagedata; //pointer to store base address of data before padding
	unsigned char* temp_data = data;	//pointer to store base address of data with padding
	
	
	/*copying actual data without padding from data with padding bytes*/
	for(int itr = 0 ; itr < lHeight ; itr++)	//loop for every column
	{
		memcpy(imagedata,data,(lWidth*BPP-1));	//copy till actual width
		imagedata+=(lWidth*BPP);	//move to next row
		data +=(lWidth*BPP+padding);	//move to next row skipping padding bytes
	}
	
	imagedata = temp_imagedata; 	//reallocating base data
	data = temp_data;
	
	
	int newimagedatasize = (newWidth*BPP*newHeight);  //size of actual data withut padding bytes
	unsigned char* newimagedata = (unsigned char*)malloc(newimagedatasize); //buffer to store rotated img data
	memset(newimagedata,250,newimagedatasize);
	if(!newimagedata)
	{
		printf("error:cannot allocate memory");
		return NULL;
	}
	PIXEL* nid = (PIXEL*)(newimagedata);	//pixel pointers to handle RBG bytes
	PIXEL* id = (PIXEL*)(imagedata);

	
	for(int n_c = 0,c = lHeight - newHeight -y ; n_c < newHeight;n_c++,c++)
	{
		for(int n_r = 0,r = x ; n_r < newWidth ;n_r++,r++)
		{
			*(nid+n_r+(n_c*newWidth)) = *(id+r+(c*lWidth)) ;
		}
	}
	
	/*update new width and height	*/
	*width = newWidth;
	*height = newHeight;	
	
	
	
	int row_stride_length = (*width)*BPP;  //new stride length
	
	if((padding = row_stride_length % 4)==0) //if padding zero
		;
	else
	{
		padding = 4 - padding; //else number of bits added for padding
	}
		
	int newdatasize =  (*height)*((*width)*BPP+padding);//calculating total bytes of raw data nad padding bytes
	
	*size = newdatasize;//updating value for passed argument
    
    	unsigned char* newdata = (unsigned char*)calloc(1,newdatasize);
    	if(!newdata)
    	{
    		printf("memory allocation error");
    		return NULL;
    	}
	
	lWidth = *width;
	lHeight = *height;
	
	temp_imagedata = imagedata;
	temp_data = newdata;
	
	for(int itr = 0 ; itr < lHeight ; itr++)
	{
		memcpy(newdata,newimagedata,(lWidth*BPP-1));
		newimagedata+=(lWidth*BPP);
		newdata +=(lWidth*BPP+padding);
	}
	
	imagedata = temp_imagedata;
	newdata = temp_data;
	
	return (char*)newdata;
	
	if(data != NULL)
		free(data);
	
	if(data != NULL)
		free(newimagedata);
	
	if(data != NULL)
		free(imagedata);
	
}


int dofree(unsigned char** ptr)
{
	if(*ptr!=NULL) 
	{
		free(*ptr); 
		*ptr = NULL;
	}
}




void main (int arg_c , char** arg_b) {
	
	FILE *fp;
	
	if(arg_c == 1)
	{
	    	fp = fopen("Default.bmp","r+b");    	
    	}
    	else if(arg_c > 1)
    	{
    		fp = fopen(*(arg_b+1),"r+b");
	}
    	
    	
     	if(!fp)
    	{	
     		printf("cannot open file");
       		return;
    	}
    	
	bitmap* bmp =(bitmap*)malloc(sizeof(bitmap));
	
	fread(bmp,sizeof(bitmap),1,fp); //load bmp header to struct;
	
	if(bmp->fh.signature[0] == 0x42 && bmp->fh.signature[1] == 0x4D)
		printf("valid bmp file");
	else
		printf("file invalid");
		
	int Bytesperpixel = bmp->bmpih.bitsperpixel/8;
	int row_stride_length = bmp->bmpih.width*Bytesperpixel;
		
	if((padding = row_stride_length % 4)==0) //if padding zero
		;
	else
	{
		padding = 4 - padding; //else number of bits added for padding
	}

	

		
	int size = (bmp->bmpih.height)*((bmp->bmpih.width)*Bytesperpixel+padding);//calculating total bytes of raw data
    
    //	printf("%d",bmp->bmpih.height);
    	
    	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char)*size); //pointer to store imgdata
    	
    //	printf("fpos %ld",ftell(fp));    	    	    	
    	
    	fread(data,size,1,fp);
	
	unsigned char* temp = data;    	


//	int padding;

	

    	int col_size = bmp->bmpih.height;

	printf("\nCHOICES: \n");
	printf("1 - HORIZONTAL FLIP \n");
	printf("2 - VERTICAL FLIP \n");
	printf("3 - ROTATE 90' \n");
	printf("4 - ROTATE 180' \n");
	printf("5 - ROTATE 270' \n");
	printf("6 - CROP \n");

	int ch ;
	scanf("%d",&ch);
	
	char* outputFileName;// = "opfile.bmp";
	
	printf("enter the name of output file...");
	
	char* s;
	while(getchar()!='\n')
		;
	
	outputFileName = get_string();

	
	FILE *ft = fopen(outputFileName,"w+b");
	if(!ft)
	{
		printf("cannot open file \n");
		return ;
	}
	
	switch(ch)
	{
		/* HORIZONTAL FLIP*/
		case 1:
		{
			hflip(data ,&(bmp->bmpih.width),&(bmp->bmpih.height), size);
			
		}
		break;
		
		/*VERTICAL FLIP*/
		case 2:
		{
		    	vflip(data ,&(bmp->bmpih.width),&(bmp->bmpih.height), size);
		}
		break;
		/*ROATE 90'*/
		case 3:
		{
		    	unsigned char* newdata = A_rotate(data ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size);
   	    		fwrite(bmp,sizeof(bitmap),1,ft);//write header to trgt
		     	fwrite(newdata,size,1,ft);
		     	
		     	dofree(&newdata);
	
		}
		break;
		/*ROATE 180'  = (rotate 90 )X 2*/
		case 4:
		{
			unsigned char* newdata = A_rotate(data ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size);
   		    	newdata = A_rotate(newdata ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size); //
   		    	
   	    		fwrite(bmp,sizeof(bitmap),1,ft);//write header to trgt
		     	fwrite(newdata,size,1,ft);
		     	
		     	dofree(&newdata);
	
		}
		/*ROTATE 270'   = (rotate 90 )X 3 */
		case 5:
		{
		    	unsigned char* newdata = A_rotate(data ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size);
   		    	newdata = A_rotate(newdata ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size);
   		    	newdata = A_rotate(newdata ,&(bmp->bmpih.width),&(bmp->bmpih.height),&size);
   		    	
   	    		fwrite(bmp,sizeof(bitmap),1,ft);//write header to trgt
		     	fwrite(newdata,size,1,ft);
		     	
		     	dofree(&newdata);
	
		}
		break;
		case 6:
		{
		    	int x;
			int y;
			int width;
			int height;
		    	do
		    	{
		    		
		    		printf("\noriginal dimension %d x %d\n",bmp->bmpih.width,bmp->bmpih.height);
		    		printf("enter the starting positions\n");
				
		    		scanf("%d",&x);
		    		scanf("%d",&y);
				
				printf("enter the width & height\n");
		    		scanf("%d",&width);
		    		scanf("%d",&height);
		    		
		    		if((x+width) < (bmp->bmpih.width) && (y+height) < (bmp->bmpih.height))
		    		{
		    			break;
		    		}
		    	
		    	}while(1);
		    	
		    	
			unsigned char* newdata = crop(data,&(bmp->bmpih.width),&(bmp->bmpih.height),&size,x,y ,width ,height);
			fwrite(bmp,sizeof(bitmap),1,ft);//write header to trgt
		     	fwrite(newdata,size,1,ft);
		     	
		     	dofree(&newdata);
	
		}
		break;
		case 0:
		{
			break;
		}
		default:
			printf("enter valid choice");
		
	}	
 	
 	
 	if(ch==1||ch==2)
    	{	
    		fwrite(bmp,sizeof(bitmap),1,ft);//write header to trgt
    	
    		fwrite(data,size,1,ft);
    	}
    	
 	
 
	dofree(&data);
	
    	
    	if(bmp!=NULL)
    	{
    		free(bmp);
    		bmp = NULL;
    	}
    	
    	fclose(fp);
    	fclose(ft);
   }
   
