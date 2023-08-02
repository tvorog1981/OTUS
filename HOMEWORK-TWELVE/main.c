#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

#define HASH_PARAMS  255
#define SIZE_ARRAY_STR 11
#define COUNT_HASH 255
#define LENGTH_STR  1024
struct _HashTab{
  int size;
  int * hash;

};

typedef struct _HashTab HashTab;


int return_hash(char * str, int size);
void print_hash(char ** str, int size);
void init_hashtab(HashTab * hash);
void free_hashtab(HashTab * hash);

void add_to_hashtab(HashTab * hash,char * w, int size){
  if( hash->hash[return_hash(w,size)] == 0){
    hash->hash[return_hash(w,size)] = 1;
    //    printf("hash %s => %d\n",w,hash->hash[return_hash(w,size)]);
  }else{
   hash->hash[return_hash(w,size)] += 1;
   //   printf(" hash %s =>%d\n",w,hash->hash[return_hash(w,size)]);
  }


}
void print_hash_to_file(char * str, int s, HashTab h){

  //  printf("hash => %d   [%s] = > %d \n",return_hash(str,s), h.hash[return_hash(str,s)]);
    printf("hash => %d [%s] => %d \n",return_hash(str,s),str,h.hash[return_hash(str,s)]);

}

void parse_file(char * file_name, HashTab * hash){
  FILE * fd = fopen(file_name,"r");
  char buff[LENGTH_STR];
  bzero(&buff,LENGTH_STR);
  int r;
  int count = 0;
  while(( r = fread(buff,sizeof(LENGTH_STR),LENGTH_STR,fd)) != 0){
   
    
    for(int j = 0 ; j < strlen(buff);j++){
      // printf("%c",buff[j]);
      if( buff[j] != '\n' && buff[j] != ' ' &&  buff[j] != '.' &&  buff[j] != '-' && buff[j] != '!'  && buff[j] != '?'){
        count++;

	  }else{
        char * word = (char *)malloc(sizeof(char) * (count+1));
	bzero(word,(count+1));
	for(int k = j - count,y = 0; k < j; k++,y++){
	  word[y] = buff[k]; 
	}
	      
        if(count == 0 ){
	  continue;	
	}else{
	  add_to_hashtab(hash,word, count);
	  // printf("count char in word %s => %d hash %d \n",word,count,return_hash(word,count) );
        }
	count = 0 ;
	free(word);
	word = NULL;
      } 
      

    }
    bzero(&buff,LENGTH_STR);
  }
  

  
  fclose(fd);
}








//main
int main(int argc,char ** argv){
  if(argc < 2 || argc > 3){
    printf("You want to %s <file> \n",argv[0]);
    exit(11);
  }



  char * array_str[SIZE_ARRAY_STR] = {"deniskina","ekaterina","roman","beer", "ev","smetankin","denis","vas","byte","bite","cash" };
  HashTab h;
  init_hashtab(&h);

  parse_file(argv[1],&h);
  for(int k = 0 ; k < SIZE_ARRAY_STR; k++)
    print_hash_to_file(array_str[k], strlen(array_str[k]),h);

  
  free_hashtab(&h);
  free_hashtab(&h);

  //    print_hash(array_str,SIZE_ARRAY_STR);



  return EXIT_SUCCESS;
}



//
int return_hash(char * str, int size){
  int hash = 0 ;
  int i = 0 ;
  while(str[i] != '\0'){
    hash += (int)(str[i]);
    i++;
  }

  //for(int i = 0 ; i < size;i++){
    // hash += (int)str[i]  + HASH_PARAMS;
    //  }
  return hash %  HASH_PARAMS;
}


//
void print_hash(char ** str, int size){
  for(int j = 0 ; j < size; j++){
    printf("hash %d [%s] => \n",return_hash(str[j],strlen(str[j]) + 1), str[j]);

  }
}  

//
void init_hashtab(HashTab * hash){
  hash->size = COUNT_HASH;
  hash->hash = (int *) malloc(sizeof(int) * hash->size);
  for(int h = 0 ; h < hash->size;h++){
    hash->hash[h] = 0 ;

  }
}
//
void free_hashtab(HashTab * hash){
  free(hash->hash);
  hash->hash = NULL;
}
