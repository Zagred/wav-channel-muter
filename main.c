
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
// da promeni short s int za da ne izmesti broya na bytovete
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
static int s_muted=0,s_unit=0;
static char unit='B',choice[1000];

//4-ta tochka
void part4(struct wav_header*header){ 
  int choice_rl=0;
  while (1)
  { 
   if(s_muted==0){
    printf("left or right\n");
   }
    scanf("%s",&choice);
    if(strcmp("right",choice))
      {
      choice_rl=0;
      break;
      }else if(strcmp("left",choice))
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
void part_1(char **file,int argc, char *argv[]){
   for(int arg=1;arg<argc;arg++){
   switch ((argv[arg])[0])
   {
   case 's':
      s_muted=1;
      break;
   case 'f':
       arg++;
       *file=argv[arg];//promenya default file-a na novia
      
      break;
   case 'u':
      arg++;
      unit=(argv[arg])[0]; 
      s_unit=1;
      break;
   } 
   }
}
//argc e poziciyata v cmd-to a argv e stringa na poziciyata
int main(int argc, char *argv[])
{
    //default path ako ne vuvedem fail
    char *file_name="C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav";
    FILE *file;
    //part1 + otvaryanae na faila v binary
    part_1(&file_name,argc,argv);
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
       int len=strlen(file_name);//duljinata na string format na file-a
       //pulnene na masiv
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
 




