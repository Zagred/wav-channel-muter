#include "sndfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <sys/stat.h>
//C:\\Users\\paco\\Desktop\\wav-channel-muter\\cheers.wav
char open_fail(char nig){
  char fail_name[100],fail_name_char;
  if(nig=='y'){
    printf("napishi location na faila:");
    scanf("%s",fail_name);
    printf("%s",fail_name);
    PlaySound(fail_name,NULL,SND_ASYNC|SND_FILENAME);
    part_1(fail_name);

  }else if(nig=='n'){
    return printf("dobre chao");
  }else{
    return printf("greshno vuvejdane");
  }
}
char part_1(char fail_path[]){
   char opening,choice_bytes;
   printf("izberi funkciya s(mute) f(fail path) u(razmeri) vsichko drugo izliza ot programta");
   scanf("%c",&opening);
   switch (opening)
   {
   case 's':
      
      break;
   case 'f':
      printf("%s",fail_path);
      break;
   case 'u':
      printf("v kakuv razmer iskash golemianta na faila B(bytes) K(Kbytes) M(Mbytes)");
      printf("%d",findSize(fail_path));
      scanf("%c",&choice_bytes);
     /* switch (choice_bytes)
      {
      case "B":
         
         break;
      case "K":
         
         break;
      case "M":
         
         break;
      
      default:
         break;
      }
      break;
      */
   default:
      break;
   }
   

}
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
int main()
{
  char choice;
  printf("izberi dali iskash da otvorish fail: y(da) n(ne)");
  scanf("%s",&choice);
  open_fail(choice);
  
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