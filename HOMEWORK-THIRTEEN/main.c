#include<stdio.h>
#include<stdlib.h>



int rev_f(int *a, int s){
   if(s == 4) return a[s] ;
   return rev_f(a,(s -1));
}

int rev_s(int *a, int s){
   if(s == 2) return a[s] ;
   return rev_s(a,(s -1));
}


int main(){
  
  int data[] = {4,8,15,16,23,42};
  int data_length = (sizeof(data) / sizeof(data[0]));
   printf("size %d \n",data_length);
  char *empty_str="";
  
  int  * arr = (int *)malloc(sizeof(int) * 2);
  if(arr == NULL){
    abort();
  }

  for(int i = 0  ; i < data_length; i++){
    printf("%d ",data[i]);

  }
  printf("\n");

   
  arr[0] = rev_f(data,data_length);
  arr[1] = rev_s(data,data_length);
    
      printf("%d %d \n",arr[0],arr[1]);
  
  free(arr);
  return EXIT_SUCCESS;
}
