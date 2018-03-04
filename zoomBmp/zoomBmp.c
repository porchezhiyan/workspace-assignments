#include <stdio.h>                                                                                   
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAGICVALUE 0x4D42
#define _BPP_RGB 3
#define _BPP_GREY 1
#define BITS_PER_BYTE 8
#define _headersize_ 54
//#define debug 1



#pragma pack(push,1)
typedef struct{
  	  uint8_t type[2];
  	  uint32_t fileSize;
  	  uint32_t reserved;
  	  uint32_t offsetToImg;
} fileHeader;
typedef struct{
    uint32_t infoHeaderSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t yPixelPerMeter;
    uint32_t xPixelPerMeter;
    uint32_t numColorsPallette;
    uint32_t mostImpColor;
} bmpInfoHeader;
typedef struct {
    fileHeader fh;
    bmpInfoHeader bmpih;
    unsigned char* data;
    
} bmpImage;
#pragma pack(pop)


typedef struct pixel
{
	unsigned char r;
	
	unsigned char g;
	
	unsigned char b;
}PIXEL;

int getZoomPercentage()
{
  do
  {
    int userip;
    printf("enter zooming percentage: \n1- 200%%  \n2- 400%%) \n3- 800%%");
    scanf("%d",&userip);
    if(userip == 1 || userip == 2 || userip ==3)
    {
      return userip;
    }
    printf("invalid option");
  }while(1);
}

int getPixelPositions(int* x_pos,int* y_pos,bmpImage* image)
{
  do
  {
    printf("image size : %d x %d ",image->bmpih.width,image->bmpih.height);
    printf("enter pixel positions");
    int x,y;
    scanf("%d%d",&x,&y);
    if(x < image->bmpih.width && y < image->bmpih.height)
    {
      *x_pos = x;
      *y_pos = y;
      return EXIT_SUCCESS;
    }
    else
    {
      printf("out of bound try again");
    }
    	
  }while(1);
}

/*is the x,y inside circle with radius 'radius' and centre (h,k)*/
int isInsideCircle(x,y,r,h,k)
int x;
int y;
int r;
int h;
int k;
{
  int lhs = (x-h)*(x-h)+(y-k)*(y-k);
  int rhs = r*r;
if(lhs <= rhs)
    return 1;
  else
    return 0;
}

/*function to zoom */
bmpImage* getZoomed(image,BPP,padding)
bmpImage* image;
int BPP;
int padding;
{
  unsigned char*dataWithPadding = image->data;
  int lHeight = image->bmpih.height;
  int lWidth = image->bmpih.width;
  int imageSize = lWidth*BPP*lHeight;


  PIXEL** pixelArray = (PIXEL**)malloc(sizeof(PIXEL*)*lHeight);//actual pixel array
  PIXEL** pixelArray2 =(PIXEL**)malloc(sizeof(PIXEL*)*lHeight*2); //pixel array of zoomed image
  if(!pixelArray||!pixelArray2)
  {
    printf("memory allocation error\n");
    return NULL;
  }
  for(int itr = 0 ; itr < lHeight ;itr++)
  {
    *(pixelArray+itr) = (PIXEL*)malloc(sizeof(PIXEL)*lWidth);  //each row of pixel array
    *(pixelArray2+itr) = (PIXEL*)malloc(sizeof(PIXEL)*lWidth*2);//each row of zoomed pixel array
    if(!(*(pixelArray+itr))||!(*(pixelArray+itr)))
    {
      printf("memory allocation error\n");
      //doFree(pixelArray);dofree(pixelArray2);
      return NULL;
    }
    *(pixelArray+itr) = memcpy((*(pixelArray+itr)),dataWithPadding,lWidth*sizeof(PIXEL)); //copy data to each row of 2-D pixel  array
    dataWithPadding += lWidth*BPP+padding; //move to next row
  }

  dataWithPadding = image->data;//reallocating base address

  for(int itr  = lHeight ; itr <lHeight*2 ; itr++)
  {
    *(pixelArray2+itr) = (PIXEL*)malloc(sizeof(PIXEL)*lWidth*2); //zoomed pixel array is twice in hyt
    if(*(pixelArray2+itr)==NULL)
    {
      printf("malloc error");
     // freeDP(pixelArray);
      //freeDP(pixelArray2);
     
      return NULL;
    }  
  }

  for(int r_itr = 0,n_r_itr = 0 ; r_itr < lWidth ;r_itr++,n_r_itr+=2)
  {
    for(int c_itr = 0,n_c_itr = 0 ; c_itr <lHeight ; c_itr++,n_c_itr+=2)
    {
//	printf("%d %d\n",ri,rj);
	*(*(pixelArray2+n_c_itr)+n_r_itr) = *(*(pixelArray+c_itr)+r_itr);// copy same position
	*(*(pixelArray2+n_c_itr+1)+n_r_itr) = *(*(pixelArray+c_itr)+r_itr);// copy adjacent down
	*(*(pixelArray2+n_c_itr)+n_r_itr+1) = *(*(pixelArray+c_itr)+r_itr);//copy adjacent right
	*(*(pixelArray2+n_c_itr+1)+n_r_itr+1) = *(*(pixelArray+c_itr)+r_itr);//copy diagonal
    }
    
  }


  int newPadding;
  int newWidth = lWidth*2;

int newHeight = lHeight*2;

  int newBytesPerRow = newWidth * BPP;
  if((newPadding=newBytesPerRow )% 4 == 0)
  {
    newPadding = 0;
  }
  else
  {

newPadding = 4 - newPadding;
  }

  int newSize = (newBytesPerRow+newPadding)*newHeight;


  unsigned char* zoomedData = (unsigned char*)calloc(newSize,1);
  if(!zoomedData)
  {
    printf("malloc error");
   // freeDP();
   // freeDP();
   // freeP();
   return NULL;

  }
  unsigned char* base = zoomedData;

  for(int itr = 0 ; itr < 2*lHeight ;itr++)
  {
   memcpy(zoomedData,*(pixelArray2+itr),newBytesPerRow); //copy from pixe buffer to zoomedData
   zoomedData+=newBytesPerRow+newPadding;	//skip padding bytes;
  }


  if(!pixelArray)
    free(pixelArray);
  if(!pixelArray2)
    free(pixelArray2);
  bmpImage* newImage =(bmpImage*)malloc(sizeof(bmpImage)); //to modify header data
  if(!newImage)
  {
    printf("malloc error");
    //freeDP();
    //freeP();
    //freep();
    return NULL;
  }
  *newImage = *image;
   newImage->bmpih.width = newWidth;
  newImage->bmpih.height = newHeight;
 
  FILE* ft;
  ft = fopen("zoomed.bmp","wb+");
  fwrite(newImage,54,1,ft);
  fwrite(base,newSize,1,ft);
  fclose(ft);

newImage->data = base;
  return newImage;
}

/*function to  cut circle*/

bmpImage* cutCircle(bmpImage* zoomImage,bmpImage* originalImage,int zoomPercentage,int x_pos,int y_pos,int BPP,int originalPadding)
{

  unsigned char* originalData = originalImage->data;

  unsigned char* zoomData = zoomImage->data;

  int zoomHeight = zoomImage->bmpih.height;
  int zoomWidth = zoomImage->bmpih.width;
  int zoomImageSize = zoomWidth*BPP*zoomHeight;

  int originalHeight = originalImage->bmpih.height;
  int originalWidth = originalImage->bmpih.width;
	
  int zoomRowBytes = zoomWidth*BPP;
  int zoomPadding;
  if((zoomPadding = zoomRowBytes%4)==0)
    zoomPadding = 0;
  else
  {
    zoomPadding =4- zoomPadding;
  }

  PIXEL** originalPixelArray = (PIXEL**)malloc(sizeof(PIXEL*)*originalHeight);//actual pixel array

  PIXEL** zoomPixelArray =(PIXEL**)malloc(sizeof(PIXEL*)*zoomHeight); //pixel array of zoomed image

  if(!originalPixelArray||!zoomPixelArray)
  {
    printf("memory allocation error\n");
    return NULL;
  
  }
  /*for original pixel array*/
  for(int itr = 0 ; itr < originalHeight ;itr++)
  {
    *(originalPixelArray+itr) = (PIXEL*)malloc(sizeof(PIXEL)*originalWidth);  //each row of pixel array
    if(!(*(originalPixelArray+itr)))
    {
      printf("memory allocation error\n");
      //doFree(pixelArray);dofree(pixelArray2);
      return NULL;
    }
    *(originalPixelArray+itr) = memcpy((*(originalPixelArray+itr)),originalData,originalWidth*BPP); //copy data to each row of 2-D pixel  array
  
    originalData+= originalWidth*BPP+originalPadding; //move to next row
  }
  printf("cp4\n");
  originalData = originalImage->data;//reallocating base address
  printf("cp3\n");
/*for zoom pixel array*/

  for(int itr = 0 ; itr < zoomHeight ;itr++)
  {
    *(zoomPixelArray+itr) = (PIXEL*)malloc(sizeof(PIXEL)*zoomWidth);  //each row of pixel array
    if(!(*(zoomPixelArray+itr)))
    {
      printf("memory allocation error\n");
      //doFree(pixelArray);dofree(pixelArray2);
      return NULL;
    }
  
    *(zoomPixelArray+itr) = memcpy((*(zoomPixelArray+itr)),zoomData,zoomWidth*sizeof(PIXEL)); //copy data to each row of 2-D pixel  array
  
    zoomData+= zoomWidth*BPP+zoomPadding; //move to next row
  }
  zoomData = zoomImage->data;//reallocating base address

  /*copying zoomed data circularly*/

  int x_posZoom = x_pos*2;
  int y_posZoom = y_pos*2;


  printf("%d %d %d %d",x_pos,y_pos,x_posZoom,y_posZoom);
 
  /*for square*/

  int frameWidth = originalWidth/3;
  int frameHeight = originalHeight/3;
  x_pos = x_pos-(frameWidth/2);
  y_pos = y_pos-(frameHeight/2);

  x_posZoom = x_posZoom-(frameWidth/2);
  y_posZoom = y_posZoom-(frameHeight/2);

  printf("%d %d %d %d",x_pos,y_pos,x_posZoom,y_posZoom);
 
  for(int c_itr = 0 ; c_itr < frameHeight ; c_itr++)
  {
    for(int r_itr = 0 ; r_itr <frameWidth ; r_itr++)
    {
      *(*(originalPixelArray+x_pos+c_itr)+y_pos+r_itr) = *(*(zoomPixelArray+x_posZoom+c_itr)+y_posZoom+r_itr);
    }
  }

  /*for square end*/


  int originalBytesPerRow = originalWidth*BPP;

  for(int itr = 0 ; itr < originalHeight ;itr++)
  {
   memcpy(originalData,*(originalPixelArray+itr),originalBytesPerRow); //copy from pixe buffer to zoomedData
   originalData+=originalBytesPerRow+originalPadding;	//skip padding bytes;
  }

  originalData = originalImage->data ;

  int size = originalHeight*(originalBytesPerRow+originalPadding);
   
  FILE* ft;
  ft = fopen("CircularZoomed.bmp","wb+");
  fwrite(originalImage,54,1,ft);
  fwrite(originalData,size,1,ft);
  fclose(ft);

  return originalImage;
}

/*main function*/
int main(int arg_c , char** arg_b)
{
  FILE* fp;
  if(arg_c == 1)
  {
    fp = fopen("2.bmp","rb+");
  }
  else{
    fp = fopen(*(arg_b+1),"rb+");
  }
  if(!fp)
  {
    printf("error: cannot open file\n");
  }
  bmpImage* image = (bmpImage*)malloc(sizeof(bmpImage));

  if(!image)
  {
    printf("memory allocation error\n");
    return EXIT_FAILURE;
  
  }
# ifdef debug
  printf("size of image : %u\n",sizeof(image));
#endif
  fread(image,54,1,fp);

  if(image->fh.type[0] == 0x42 && image->fh.type[1] == 0x4D)
    printf("valid bmp file\n");
  else
  {
  	printf("file invalid");
  	return EXIT_FAILURE;
  }
  int padding;

  int BPP = image->bmpih.bitsPerPixel/BITS_PER_BYTE;
  int row_stride_length = image->bmpih.width*BPP;
  if((padding = row_stride_length % 4)==0) //if padding zero
		;
  else
  {
    padding = 4 - padding; //else number of bits added for padding
  }
  int size = (image->bmpih.height)*((image->bmpih.width*BPP)+padding);//calculating total bytes of raw data

//  printf("%d",bmp->fh.offset_to_img);

  image->data = (unsigned char*)malloc(sizeof(unsigned char)*size); //pointer to store imgdata
  if(!image->data)
  {
    printf("cannot allocate memory");
    return EXIT_FAILURE;
  }

  fread(image->data,size,1,fp);

  int zoomPercentage;
  zoomPercentage = getZoomPercentage();
  int x_pos,y_pos;
  getPixelPositions(&x_pos,&y_pos,image);


  int ch = 0;
  do
  {
  
    printf("frame shape\n");  
    printf("1.horizontal ellipse\n");
    printf("2.vertical ellipse\n");
    printf("3.square\n");
    printf("4.circle\n");
    scanf("%d",&ch);
    switch(ch)
    {
      /*hztl ellipse*/
        case 1:
	{



	  break;
	}

	/*vrtcl ellipse*/
	case 2:
	{

	  break;
	}
	/*square*/
	case 3:
	{
	

	  break;
	}
	/*circle*/
	case 4:
	{

	  bmpImage* finalImage = getZoomed(image,BPP,padding);
	  if(finalImage==NULL)
		  return EXIT_FAILURE;
	 printf("beforecutcircle\n"); 
	  finalImage = cutCircle(finalImage,image,zoomPercentage,x_pos,y_pos,BPP,padding);

	}
	/*plain zoom*/
	case 5:
	{

	  break;
	}

	/*exit*/
	case 0:
	{

	  break;
	}
	default:
		printf("enter valid choice\n");

    }
  
  }while(ch!=0);
	
  fclose(fp);

}

