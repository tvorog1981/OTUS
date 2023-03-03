#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct header_tar tar_s;

  struct header_tar {
                   char name[100];
                   char mode[8];
                   char uid[8];
                   char gid[8];
                   char size[12];
                   char mtime[12];
                   char checksum[8];
                   char linkflag[1];
                   char linkname[100];
                   char pad[255];
           };


int main(int argc ,char ** argv){
  if(argc < 2){
    printf(" You want to %s \"<zip archive>\" \n", argv[0]);
    exit(1);
  }

  

  FILE *  fd  = fopen(argv[1],"r");

  int i = 0;
  if(fd){
         //char  b;
	//	int i = 0;
        //tar_s * tt;
	while(!feof(fd)){
	 tar_s * tt = (tar_s *) malloc(sizeof(tar_s));
	 memset(tt,0, sizeof(tar_s));
	 // printf("\nsize %ld\n",sizeof(tt));
	  if(0 < fread(tt,sizeof(tar_s),1,fd)){

	    if(i == 0){
              fprintf(stdout,"Name is archive -> %s\n",tt->name);
              i++;
	    }else if(strlen(tt->name) != 0){
	      fprintf(stdout,"file %d -> %s  size -> %s \n",i, tt->name, tt->size);
	    i++;
	    }  

	  }
	     
	  free(tt);	  
 
	}
	printf("####COUNT FILES IN ARCHIVE %d ####\n",i -1);
	fclose(fd);
  }
	return 0;
}
