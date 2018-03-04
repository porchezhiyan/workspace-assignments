#include <stdio.h>                                                                                   
#include <stdint.h>
#include <string.h>
#include<stdlib.h>
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

void main () {
    FILE *fp = fopen("f1.bmp","r+b");
    FILE *ft = fopen("f2.bmp","w+b");
    if(!fp)
    {
       printf("cannot open file");
       return;
    }
    bitmap* bmp =(bitmap*)malloc(sizeof(bitmap));
    fread(bmp,sizeof(bitmap),1,fp); //load bmp header to struct;
	
	fwrite(bmp,sizeof(bitmap),1,ft);//write data
	
		//	    	    printf("fpos%ld",ftell(ft));
	
	int size = (bmp->bmpih.height)*(bmp->bmpih.width)*(bmp->bmpih.bitsperpixel/8);//calculating total bytes of raw data

   	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char)*size); //pointer to store imgdata
    	
    	fseek(fp,bmp->fh.offset_to_img,SEEK_SET);//starting of data
    	

	printf("fpos %ld",ftell(fp));    	    	    	
    	
    	fread(data,size,1,fp);//read data
    	

    	

    	int row_size = bmp->bmpih.width*bmp->bmpih.bitsperpixel/8;
    	int col_size = bmp->bmpih.height*3;

		printf("rsize %d",row_size);    	    	    			
		
    	for(int k = 0 ; k < 338 ;k++)
    	{
    		for(int itr = 0; itr<row_size/2 ; itr+=3)
    		{
    			unsigned char temp = *(data+itr+(k*row_size));
    			*(data+itr+(k*row_size)) = *(data-itr+(row_size-1)-2+(k*row_size));
    			*(data-itr+row_size-2-1+(k*row_size)) = temp;
    				
    			temp = *(data+itr+1+(k*row_size));
    			*(data+itr+1+(k*row_size)) = *(data-itr+row_size-1-1+(k*row_size));
    			*(data-itr+row_size-1-1+(k*row_size)) = temp;
    				
    			temp = *(data+itr+(k*row_size));
    			*(data+itr+(k*row_size)) = *(data-itr+row_size-1+(k*row_size));
    			*(data-itr+row_size-1+(k*row_size)) = temp;
    	}	
    	}
    	
    	
    	
    
    /*
    	for(int c_itr = 0 ; c_itr <column_size  ;c_itr++)
    	{
    		for(int r_itr = 0 ; r_itr <(row_size/2)  ;r_itr+=3)
    		{
    			
    			unsigned char temp = *(data+r_itr+(row_size*c_itr));
    			*(data+r_itr+(row_size*c_itr))=*(data+(row_size*c_itr)-r_itr+row_size-3);
    			*(data+(row_size*c_itr)+r_itr+row_size-3) = temp;
    			
    			
    			temp = *(data+r_itr+(row_size*c_itr)+1);
    			*(data+r_itr+(row_size*c_itr)+1)=*(data+(row_size*c_itr)-r_itr+row_size-2);
    			*(data+(row_size*c_itr)+r_itr+row_size-2) =temp;
    			
    			temp = *(data+r_itr+(row_size*c_itr)+2);
    			*(data+r_itr+(row_size*c_itr)+2)=*(data+(row_size*c_itr)-r_itr+row_size-1);
    			*(data+(row_size*c_itr)+r_itr+row_size-1) =temp;
    			
    			
    			
//    			*(data+r_itr+(row_size*c_itr)+2)=*(data+(row_size*c_itr)+2+r_itr+row_size/2);
    		
    			
    		}
    	
    	}
    	
    */
    	//fclose(fp);
    	
    	//fp = fopen("BLK.BMP","wb+");
    	//fwrite(&bmp,sizeof(bitmap),1,fp);
    	
    	
    	 
		    	   fseek(ft,bmp->fh.offset_to_img,SEEK_SET);
		    	    
		   // 	    printf("fpos%ld",ftell(ft));
		
		    	    fwrite(data,size,1,ft);
    
 	//	    	    printf("%ld",ftell(fp));
 
 
 
   fclose(fp);
}

