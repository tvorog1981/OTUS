#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define SIZE_ARRAY_BITS 5

typedef struct _zip zip;



struct _zip {
  char head[23];
  int8_t filenameLength; 
  char footer[17];
};



/*function create file description */
int create_file_des(const  char * file){

  int fd  = open(file , O_RDONLY);
  /*checked file on create*/
  if(0 > fd ){
    printf("did't open  %s \n",file);
    exit(1);
  }

  
  return fd;
}

/*closed file descriptor*/
void destroy_file_des(int fd){

  close(fd);
}
/* created array bits */
void insert_bits(char * a){a[0] = 0x50; a[1] = 0x4B; a[2] = 0x01; a[3] = 0x02;}

/* read zip archive*/

void read_file_zip_archive(int fd ,char *a ,int size){

  char * aa = a;
  char buff[256];
  char c;
  size_t size_read;
  int count = 0;
  int count_find_file = 0;
  zip zip_archive;
  
  while((size_read = read(fd,&c, 1)) > 0){
    if((c == aa[0] || aa[0] == 0x0) && count < size){
      //      printf("%c",c);
      aa++;
      count++;
    }else{
      aa = a;
      count = 0 ;
 
    }
    
    if(count == size){
      bzero(&zip_archive,sizeof(zip_archive));         
      read(fd,(zip *)&zip_archive,sizeof(zip_archive));

      // printf( " -> %ud <- \n",zip_archive.str_len);
      read(fd,&buff,zip_archive.filenameLength);
      buff[zip_archive.filenameLength] = '\0';
      printf( " number of file [ %d ] -> %s  \n",count_find_file++,buff);
      count_find_file++;
      aa=a;
      count= 0;
    }

    }
  if(count_find_file){
  
    
  }else{
       printf("file dont have archive \n");
  }
}




int main(int argc ,char ** argv){

  int fd = create_file_des(argv[1]);


  char array_bits[SIZE_ARRAY_BITS];

  insert_bits(array_bits);

  read_file_zip_archive(fd ,array_bits,SIZE_ARRAY_BITS);

  

  destroy_file_des(fd);




  return EXIT_SUCCESS;
}
