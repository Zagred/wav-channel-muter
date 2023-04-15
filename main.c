#include "sndfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>

static int s_muted=0;
 int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}
void part_1(char **file,int argc, char *argv[]){
   int do_find_size=0;
   for(int arg=1;arg<argc;arg++){
   switch ((argv[arg])[0])
   {
   case 's':
      s_muted=1;
      printf("%d \n",s_muted);
      break;
   case 'f':
      arg++;
       *file=argv[arg];
       if(s_muted==0){ 
       printf("%s \n",*file);
       }
      break;
   case 'u':
      do_find_size=1;
      printf("u \n");
      break;
   default:
      printf("error!!!!");
      break;
   } 
   }
   if(s_muted==0){
   if(do_find_size){
    int byte=findSize(*file); 
    printf("%d \n",byte);
    char artibute='B';
    if(byte>1024){
      byte/=1024;
      artibute='K';
    }
    if(byte>1024){
      byte/=1024;
      artibute='M';
    }
    printf("%d %c",byte,artibute);
    } 
   }
}
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\cheers.wav
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav
int main(int argc, char *argv[])
{
    char *fail="C:\\Users\\paco\\Desktop\\wav-channel-muter\\test.wav";
    part_1(&fail,argc,argv);
    PlaySound(fail,NULL,SND_SYNC|SND_FILENAME);
  
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