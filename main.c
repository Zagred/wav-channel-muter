#include "sndfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
// da promeni short s int za da ne izmesti broya na bytovete
#pragma pack(push,1)
struct wav_header{
   int Chunk_ID;
   int Chunk_Size;
   int Format;
   int Subchunk1ID;
   int Subchunk1Size;
   short AudioFormat;
   short NumChannels;
   int SampleRate;
   int ByteRate;
   short BlockAlign;
   short BitsPerSample;
   char Subchunk2ID;
   int Subchunk2Size;
};
#pragma pack(pop)
static int s_muted=0,counter=0;
static char unit='B',choice[1000];
//4-ta tochka
short * stereoChannel;
short * leftChannel;
short * rightChannel;
int     val     =    50000;

void part4(FILE *file,struct wav_header*header){ 
  while (1)
  {
    printf("left or right\n");
    scanf("%s",&choice);
    if(choice[0]=='l'||choice[0]=='r'){
      break;
    }
  }
  printf("choice:%s\n",choice);
   fseek(file,44,SEEK_SET);
   int num;
   fread(&num,sizeof(int),1,file);
   stereoChannel = malloc(num*sizeof(short));
   fseek(file,4,SEEK_CUR);
   fread(stereoChannel,sizeof(short),num,file);
      printf("wavfile in stereo\n");
      for (int inc=0;inc<header->Subchunk2Size/2;inc++){
         if(choice[0]=='l'){
          if(stereoChannel[inc*2]!=0){   
            stereoChannel[inc*2]=0;
            counter++;
          }
         }else if(choice[0]=='r'){
          if(stereoChannel[(inc*2)+1]!=0){
            stereoChannel[(inc*2)+1]=0;
            counter++;
          }
         }
      }

      printf("<%d> samples on the <%s> channel were replaced with 0",counter,choice);
  
    
}
//3-ta tochka
void part3(int sound_content_size){
   if(unit>='a'){
      unit-=32;
   }
   switch (unit)
   {
   case'B':
      unit=0;
      break;
   case'K':
      sound_content_size/=1024;
      break;   
    case'M':
      sound_content_size/=1024;
      sound_content_size/=1024;
      break;
   default:
      break;
   }
   printf("the sound of content is %d %cB \n",sound_content_size,unit);

}
//2-ra tochak ot zadacahta
void part2(struct wav_header*header){  
    printf("number of channels:%d\n",header->NumChannels);     
}
//1-va tochka ot zadacahta
void part_1(char **file,int argc, char *argv[]){
   for(int arg=1;arg<argc;arg++){
   switch ((argv[arg])[0])
   {
   case 's':
      s_muted=1;
      break;
   case 'f':
       arg++;
       *file=argv[arg];
       if(s_muted==0){ 
       printf("%s \n",*file);
       }
      break;
   case 'u':
      arg++;
      unit=(argv[arg])[0]; 
      break;
   } 
   }
}

//C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\slay.wav
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\poe_whisper.wav

int main(int argc, char *argv[])
{
    //
    char *file_name="poe_wispers.wav";
    FILE *file;
    //
    part_1(&file_name,argc,argv);
    file=fopen(file_name,"rb");
    //
    fseek(file, 0L, SEEK_END);//otiva na kraya na faila
    int size = ftell(file); 
    //
    char *data=malloc(size);
    fseek(file, 0L, SEEK_SET);//otiva v nachaloto na faila
    fread(data,1,size,file);//iska size za tova pochvame ot  purvo ot kraya i posle se vrushtame v nachaloto

    struct wav_header*header=(struct wav_header*)data;
    
    //
    if(s_muted==0){
    part2(header);

    int sound_content_size=header->Subchunk2Size;
    part3(sound_content_size);
    
    if(header->NumChannels==2){
     printf("stereo \n");
       
       part4(file,header);
    } 
    }
    PlaySound(file_name,NULL,SND_SYNC|SND_FILENAME);
    //PlaySound(file_name,NULL,SND_FILENAME|SND_MEMORY);

}
 




