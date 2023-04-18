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
   int Subchunk2ID;
   int Subchunk2Size;
};
#pragma pack(pop)
static int s_muted=0;
static char unit='B';
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
   printf("the sound of content is %d %cB",sound_content_size,unit);

}
//2-ra tochak ot zadacahta
void part2(struct wav_header*header){
 if(s_muted==0){   
    printf("number of channels:%d\n",header->NumChannels);
    }
   
}
//1-va tochka ot zadacahta
void part_1(char **file,int argc, char *argv[]){
   *file=argv[1];
   for(int arg=1;arg<argc;arg++){
   switch ((argv[arg])[0])
   {
   case 's':
      s_muted=1;
      break;
   case 'f':
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

//C:\\Users\\paco\\Desktop\\wav-channel-muter\\cheers.wav
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav
int main(int argc, char *argv[])
{
    //
    char *file_name="C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav";
    FILE *file;
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
    part_1(&file_name,argc,argv);
    part2(header);
    int sound_content_size=header->Subchunk2Size;
    part3(sound_content_size);
    //PlaySound(file_name,NULL,SND_SYNC|SND_FILENAME);
    
  
/*short * stereoChannel;

short * leftChannel;
short * rightChannel;

char    Subchunk2[4];
int     move    =    0;
short   channel =    1;
int     val     =    50000;

int main(){

   FILE *fp = fopen("C:\\Users\\paco\\Desktop\\wav-chan\\test.wav","rb+");
   if (!fp){
      printf("Couldn't open file!\n");
      return 0;
   }
   while (1){
     fseek(fp,36+move,SEEK_SET);
     fread(Subchunk2,4*sizeof(char),1,fp);
     if (!strcmp(Subchunk2,"data")){
        break;
     }
     move++;
   }
   fseek(fp,22,SEEK_SET);
   fread(&channel,sizeof(short),1,fp);
   fseek(fp,36+move+4,SEEK_SET);
   int num;
   fread(&num,sizeof(int),1,fp);
   stereoChannel = malloc(num*sizeof(short));
   fseek(fp,4,SEEK_CUR);
   fread(stereoChannel,sizeof(short),num,fp);
   if (channel == 2){
      val=0;
      printf("wavfile in stereo\n");
      leftChannel = malloc(num*sizeof(short)/2);
      rightChannel = malloc(num*sizeof(short)/2);
      int channelpoint = 0;
      for (int inc=0;inc<num/2;inc++){
         leftChannel[channelpoint] = stereoChannel[inc*2];
         rightChannel[channelpoint] = stereoChannel[(inc*2)+1];
         channelpoint++;
      }



      for (int k=0; k<50000; k++){
         printf("stereo sample %d L: %d R: %d \n",k,leftChannel[k],rightChannel[k]);
      }

      free(rightChannel);
      free(leftChannel);
   }
   for (int k=0; k<val; k++){  // If this is stereo, it would print nothing because val was set to 0
      printf("mono sample %d is %d\n", k, stereoChannel[k]);
}
   free(stereoChannel);
   return 0;
}

// FILE *fp = fopen("C:\\Users\\paco\\Desktop\\wav-chan\\cheers.wav","rb+");
*/
}