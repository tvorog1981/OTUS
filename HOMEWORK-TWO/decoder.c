#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdint.h>
#include "encoding.h"
/*  check of choose encoding*/
int choose_encoding(char * argv){
  char * arr_encoding[3]={"koi8-r","cp-1251","iso-8859-5"};
  int rez = -1;
  if(strncmp(argv,arr_encoding[0], strlen(arr_encoding[0])) == 0 ){
    rez = 1;
    return rez;
  }
   if(strncmp(argv,arr_encoding[1], strlen(arr_encoding[1])) == 0 ){
     rez = 2;
    return rez;
  }
   if(strncmp(argv,arr_encoding[2], strlen(arr_encoding[2])) == 0 ){
    rez = 3;
    return rez;
  }
    

  return rez;
}


/* functions encoding */
void encoding_koi8_r(char * s,char * d){
  /* flags open and create file */
  int flag =  O_WRONLY | O_CREAT;
  /* mode create file */
  mode_t mode = S_IRUSR | S_IWUSR;
/* files description */
  int fd_s = open(s,O_RDONLY);
  int fd_d = open(d,flag,mode);
  /* check file description */
  if(0 > fd_s || 0 > fd_d){
    printf("Can not create file description \n ");
    exit(1);    
  }
    /* read file */
  uint8_t ch;
  size_t  count_read_bit;
    while( (count_read_bit =read(fd_s,&ch,sizeof(ch))) > 0 ){
   if(ch >= 192 && ch <= 255){    
       uint16_t code = unicode_koi8r[ch -192];
       uint8_t buff[2]={0};
       
	if(ch <=0x7F){
	 code = (uint8_t)code;
	  // printf("|ch -> %c |",ch);
	  write(fd_d,&code, sizeof(code));
     	  
	}

        else if(code  <= 0x07FF){
	
		 buff[0] = (uint8_t)(((code >> 6) & 0x1F)| 0xc0);
	 buff[1]= (uint8_t)(((code >>  0)  & 0x3F) | 0x80);
	 // printf("%s ->  ",buff);
	 write(fd_d,&buff, sizeof(buff));
	 }
		
     }else{
              write(fd_d,&ch, sizeof(ch));
	   }

    }

		   
  
  /* close file description */
  close(fd_s);
  close(fd_d);
}
void   encoding_cp_1251(char * s ,char * d){
  /* flags open and create file */
  int flag =  O_WRONLY | O_CREAT;

  /* mode create file */
  mode_t mode = S_IRUSR | S_IWUSR;

  /* files description */
  int fd_s = open(s,O_RDONLY);
  int fd_d = open(d,flag,mode);

  /* check file description */
  if(0 > fd_s || 0 > fd_d){
    printf("Can not create file description \n ");
    exit(1);
    
  }
  
  /* read file */
  uint8_t ch;
  size_t  count_read_bit;
 

    while( (count_read_bit =read(fd_s,&ch,sizeof(ch))) > 0 ){


         if(ch >= 192 && ch <= 255){
      
    
	uint16_t code = unicode_win1251[ch -191];
	uint8_t buff[2]={0};
       

	if(code <=0x7F){
	  buff[0] = (uint8_t)code;
	  write(fd_d,&buff, sizeof(buff));
     	  
	}

        else if(code  <= 0x07FF){
	
		 buff[0] = (uint8_t)(((code >> 6) & 0x1F)| 0xc0);
		 buff[1]= (uint8_t)(((code >>  0)  & 0x3F) | 0x80);
	         write(fd_d,&buff, sizeof(buff));
	 }
	 
	
	 }else{
              write(fd_d,&ch, sizeof(ch));
	   }

    }

		   
  
  /* close file description */
  close(fd_s);
  close(fd_d);
}

void  encoding_iso_8859_5(char * s ,char * d){
  /* flags open and create file */
  int flag =  O_WRONLY | O_CREAT;

  /* mode create file */
  mode_t mode = S_IRUSR | S_IWUSR;

  /* files description */
  int fd_s = open(s,O_RDONLY);
  int fd_d = open(d,flag,mode);

  /* check file description */
  if(0 > fd_s || 0 > fd_d){
    printf("Can not create file description \n ");
    exit(1);
    
  }
  
  /* read file */
  uint8_t ch;
  size_t  count_read_bit;
  
    while( (count_read_bit =read(fd_s,&ch,sizeof(ch))) > 0 ){
         if(ch >= 176 && ch <= 239){
	  uint16_t code = unicode_win1251[ch -176 + 1];
           uint8_t buff[2] = {0};
       	if(code <=0x7F){
	 buff[0] = (uint8_t)code;	  
	 write(fd_d,&buff, sizeof(buff));  	  
	 	}

	   else if(code  <= 0x07FF){
	
	 	 buff[0] = (uint8_t)(((code >> 6) & 0x1F)| 0xc0);
	   buff[1]= (uint8_t)(((code >>  0)  & 0x3F) | 0x80);
	   //  printf("%s ->  ",buff);
	   write(fd_d,&buff, sizeof(buff));
	   }
	  

	
	
     }else{
              write(fd_d,&ch, sizeof(ch));
	   }

    }

  /* close file description */
  close(fd_s);
  close(fd_d);

}



/* Main function */
int main(int argc ,char ** argv){

  /*check input argc  */
  if(argc < 4 || argc > 4){
    printf(" You want %s <file> <encoding> <file> \n",argv[0]);
    exit(1);

  }

  int encoding = choose_encoding(argv[2]);
  // printf("return %d \n",encoding);

  /* check return value */
  if(encoding == -1){
    printf("Encoding don't have in programm\n");
    printf("Encoding cp-1251, koi8-r,iso-8859-5\n");
    exit(1);
  }

  switch(encoding){
  case 1:{
    encoding_koi8_r(argv[1],argv[3]);
    
    break;
  }
  case 2:{
     encoding_cp_1251(argv[1],argv[3]);
    break;
  }
  case 3:{
       encoding_iso_8859_5(argv[1],argv[3]);
    break;
  }
  default:{
    printf("errror");
  }
  }

  return EXIT_SUCCESS;
}
