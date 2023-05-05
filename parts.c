
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
#pragma pack(push,1)
struct wav_header{//struktura na celia header int-4 short-2
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
   int Subchunk2ID;
   int Subchunk2Size;
};
#pragma pack(pop)
static int s_muted=0,s_unit=0,f_file=0;
static char unit='B',choice[1000],wav_name[1000];

//4-ta tochka
void part4(struct wav_header*header){ 
  int choice_rl=0;
  while (1)
  { 
   if(s_muted==0){
    printf("left or right\n");
   }
    scanf("%s",choice);
    if(strcmp("right",choice)==0)
      {
      choice_rl=0;
      break;
      }else if(strcmp("left",choice)==0)
      {
      choice_rl=1;
      break;
      }
  }      
   if(s_muted==0){
    printf("choice:%s\n",choice);
   }
    short *samples=(short*)((char*)header+44)+choice_rl;//
    int counter=0;//koi sampali sa zameneni ot neshto kum 0
      for (int inc=0;inc<header->Subchunk2Size/sizeof(short);inc+=2){//edin left/right sample e short(2 bite) i prezkachame s  2 za da hodi samo ot edinia vid
         if(samples[inc]!=0){
          counter++;
         }
         samples[inc]=0;
      }
     if(s_muted==0){
     printf("<%d> samples on the <%s> channel were replaced with 0",counter,choice);
     }
  
    
}
//3-ta tochka
void part3(int sound_content_size){
  if(s_unit==1){ 
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
   if(s_muted==0){
   printf("the sound of content is %d %cB \n",sound_content_size,unit);
   }
   }else if(s_unit==0){
      if(sound_content_size>1048576){
         unit='M';
      }else if(sound_content_size>1024 && sound_content_size<1048576){
         unit='K';
      }else{
         unit='B';
      }
      s_unit=1;
      part3(sound_content_size);
   }
    
}
//2-ra tochak ot zadacahta
void part2(struct wav_header*header){  
   if(s_muted==0){  
      printf("number of channels:%d\n",header->NumChannels);
   }     
}
//1-va tochka ot zadacahta
void part_1(int argc, char *argv[]){
   for(int arg=1;arg<argc;arg++){
   switch ((argv[arg])[0])
   {
   case 's':
      s_muted=1;
      break;
   case 'f':
       arg++;
       f_file=1;
       int len=strlen(argv[arg]);
       for(int i=0;i<=len;i++){
         wav_name[i]=(argv[arg])[i];
       }
      break;
   case 'u':
      arg++;
      unit=(argv[arg])[0]; 
      s_unit=1;
      break;
   } 
   }
}
 




