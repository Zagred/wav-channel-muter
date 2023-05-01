
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
#include "parts.c"

//argc e poziciyata v cmd-to a argv e stringa na poziciyata
int main(int argc, char *argv[])
{
    //default path ako ne vuvedem fail
    char *file_name="C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav";
    FILE *file;
    //part1 + otvaryanae na faila v binary
    part_1(&file_name,argc,argv);
    //proveryava dali e wav file
    char wav_name[1000],wav[3];
    int len=strlen(file_name);
        for(int i=0;i<len;i++){
         wav_name[i]=file_name[i];
       }
       for(int i=0;i<len;i++){
         if(wav_name[i]=='.'){
            wav[0]=wav_name[i+1];
            wav[1]=wav_name[i+2];
            wav[2]=wav_name[i+3];
            wav_name[i]=0;
         }
       }
       if(strcmp(wav,"wav")!=0){
         printf("not a wav file");
         return 0;
       }
    file=fopen(file_name,"rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", file_name);
      }
    //vzimane na razmera na faila
    int ret=fseek(file, 0L, SEEK_END);//otiva na kraya na faila
    int size = ftell(file); 
    //locatvame memory i vrushtame v nachaloto na faila
    char *data=malloc(size);
    fseek(file, 0L, SEEK_SET);//otiva v nachaloto na faila
    fread(data,1,size,file);//iska size za tova pochvame ot  purvo ot kraya i posle se vrushtame v nachaloto
    //struktura za "headera" na faila 
    struct wav_header*header=(struct wav_header*)data;
    
    //part2 i 3 +vzimane na sound contenta
    part2(header);
    int sound_content_size=header->Subchunk2Size;
    part3(sound_content_size);
    //part4+ proverka za mono ili stereo file+ pri stereo file da napravi nov s promenite
    if(header->NumChannels==2)
    {
       part4(header);
       char new_name[1000];
       for(int i=0;i<len;i++){
         new_name[i]=file_name[i];
       }
       //vzimane na stringa vsichko bez ".wav"  
       for(int i=len;i>0;i--){
         if(new_name[i]=='.'){
            new_name[i]=0;//0 e za prekratyavane na stringa
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
    
    PlaySound((LPCSTR)header,NULL,SND_SYNC|SND_MEMORY);//playva sounde ot memory toest momentnia file koito bachka programta
    
}
 




