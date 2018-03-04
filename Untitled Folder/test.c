#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
  unsigned short bfType;
  unsigned bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned bfOffBits;
}BITMAPFILEHEADER;



typedef uint32_t DWORD;   // DWORD = unsigned 32 bit value
typedef uint16_t WORD;    // WORD = unsigned 16 bit value
typedef uint8_t BYTE;     // BYTE = unsigned 8 bit value

#pragma pack(pop)

//typedef  unsigned short WORD;
//typedef unsigned DWORD;

#pragma pack(push,1)
typedef struct tagBITMAPINFOHEADER
{
  DWORD biSize;
  DWORD biWidth;
  DWORD biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  DWORD biXPelsPerMeter;
  DWORD biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;

}BITMAPINFOHEADER;
#pragma(pop)

unsigned char* loadBitMapFile(char* filename , BITMAPINFOHEADER* bitmapInfoHeader)
{
  FILE* fp;
  BITMAPFILEHEADER bitmapfileheader;
  unsigned char* bitMapImage;
  int imageIdx=0;
  unsigned char tempRGB;
  fp = fopen(filename,"rb");
  if(fp ==NULL)
  {
    printf("cannot open file");
    return NULL;
  }
  fread(&bitmapfileheader,sizeof(BITMAPFILEHEADER),1,fp);
  if(bitmapfileheader.bfType!= 0x4D42)
  {
    printf("wronf file type");
    return NULL;
  }
  fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fp);
  fseek(fp,bitmapfileheader.bfOffBits,SEEK_SET);
  bitMapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
  if(!bitMapImage)
  {
    printf("cannot allocate memory");
    fclose(fp);
    return NULL;
  }
  fread(bitMapImage,bitmapInfoHeader->biSizeImage,1,fp);

  if(bitMapImage == NULL);
  {
    fclose(fp);
    return NULL;
  }
  for(imageIdx = 0 ; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
  {
    tempRGB = bitMapImage[imageIdx];
    bitMapImage[imageIdx] = bitMapImage[imageIdx+2];
    bitMapImage[imageIdx+2] = tempRGB;
  }
  fclose(fp);
  return bitMapImage;
}





void main()
{


  BITMAPINFOHEADER bitmapInfoHeader;

  unsigned char* bitmapData;

  bitmapData = loadBitMapFile("BLK.BMP",&bitmapInfoHeader);
  printf("bitmap data: %s ",bitmapData);
}





