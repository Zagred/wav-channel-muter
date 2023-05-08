
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
#include "parts.c"
int main(int argc, char *argv[])
{
    FILE *file;
    //part1 + opens the file in binary
    part_1(argc,argv);
    if(f_file==0){
      scanf("%s",wav_name);
    }
    //check the file if is a wav file
    char wav[4];
    int len=strlen(wav_name);
      for(int i=len;i>=0;i--){
         if(wav_name[i]=='.'){
            wav[0]=wav_name[i+1];
            wav[1]=wav_name[i+2];
            wav[2]=wav_name[i+3];
            wav[3]=0;
         }
      }
       if(strcmp(wav,"wav")!=0){
         printf("not a wav file");
         return 0;
       }
    file=fopen(wav_name,"rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", wav_name);
      }
    //gets the size of the file
    int ret=fseek(file, 0L, SEEK_END);//goes to the end of the fail
    int size = ftell(file); 
    //locating memory and goest to the start of the file
    char *data=malloc(size);
    fseek(file, 0L, SEEK_SET);
    fread(data,1,size,file);//for the size we need to check from end to start
    //struct
    struct wav_header*header=(struct wav_header*)data;
    
    //part2 i 3 + we get a size content
    part2(header);
    int sound_content_size=header->Subchunk2Size;
    part3(sound_content_size);
    //part4+ chesk if the file is mono or stereo + if stereo it makes changes 
    if(header->NumChannels==2)
    {
       part4(header);
       char new_name[1000];
       for(int i=0;i<len;i++){
         new_name[i]=wav_name[i];
       }
       //we get everything expect ".wav"  
       for(int i=len;i>0;i--){
         if(new_name[i]=='.'){
            new_name[i]=0;//0 is the end of string
         }
       }
       char new_file_name[1000];
       snprintf(new_file_name,sizeof(new_file_name),"%s-%s-channel-muted.wav",new_name,choice);
       FILE* new_file=fopen(new_file_name,"wb");
        if (new_file == NULL) {
        printf("Failed to open file: %s\n", new_file_name);
      }
       fwrite(data,sizeof(char),size,new_file);
    }
    
    PlaySound((LPCSTR)header,NULL,SND_SYNC|SND_MEMORY);//playing sound from memory 
    
}
 




