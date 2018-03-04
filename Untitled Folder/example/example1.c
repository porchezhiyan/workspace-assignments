#include <stdio.h>
#include <stdlib.h>
     
#pragma pack(push,1) 
struct BMP
{
  char Type[2];           //File type. Should be "BM".
  unsigned long Size;     //Size in BYTES of the file.
  unsigned long Reserved;      //Reserved. Set to zero.
  unsigned long OffSet;   //Offset to the data.
  unsigned long headsize; //Size of rest of header. Set to 40.
  unsigned long Width;     //Width of bitmap in pixels.
  unsigned long Height;     //  Height of bitmap in pixels.
  unsigned int  Planes;    //Number of Planes. Set to 1.
  unsigned int  BitsPerPixel;       //Number of Bits per pixels.
  unsigned long Compression;   //Compression. Usually set to 0.
  unsigned long SizeImage;  //Size in bytes of the bitmap.
  unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
  unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
  unsigned long ColorsUsed;   //Number of colors used.
  unsigned long ColorsImportant;  //Number of "important" colors.
};
#pragma pack(pop)

int ShowBMP(char* FileName)
{
        
  struct BMP Obj;

  FILE * fp;

  fp = fopen(FileName,"rb");
  if(!fp){
    printf("Error : Unable to open file ..");
    exit(0);
  }
  
  fread(&Obj, sizeof(Obj), 1, fp);
  char* data;
  fseek(fp,Obj.OffSet,SEEK_SET);
  fread(data,Obj.SizeImage,1,fp);
  fclose(fp);
//  printf("%ld %c",sizeof(Obj),Obj.Type[1]);
  for(int i = 0 ; i < Obj.SizeImage ;i++)
  {
     printf("%c",*(data+i));
  }
  
  return 1;
}
void main()
{
     
  printf("res: %d",ShowBMP("BLK.BMP")); /* Enter File Name Here */
}
