#include<stdio.h>
#include<stdlib.h>



typedef int Data;
typedef struct Node Node;

int data[] ={4, 8, 15, 16, 23, 42};
int length = 6;
struct Node{
  Data  data;
  Node * next;

};

void print_all(Node * list){
  for(Node * p = list; p != NULL; p= p->next){
    printf("%d ",p->data);
  } 
  printf("\n");
}


void add_element(Node ** list ,int value){
  if(*list == NULL){
    Node * new_elem = (Node *)malloc(sizeof(Node));
 
  new_elem->data = value;
  new_elem->next = *list;
  *list = new_elem;
  
  }else{  
  Node * start = *list;
  while( (*list)->next != NULL ){
      *list = (*list)->next;
    }
  Node * new_elem = (Node *)malloc(sizeof(Node));

  new_elem->next = NULL;
  new_elem->data = value;
  (*list)->next = new_elem;
  *list = start;
  }
}


void free_list(Node ** list){

  for(; *list != NULL;){
    Node *buff = (*list)->next;
    free(*list);
    *list = buff;  
  }
  

}

void print_int(Node * list ,int elem){
  for(Node *p = list ; p !=NULL; p=p->next){
    if(elem == p->data){
      printf("%d ",p->data);
    }

  }

}

int main(){
  struct Node * list = NULL;
  for(int i = 0 ; i < length; i++){
    add_element(&list,data[i]);
  }

  print_all(list);
  print_int(list,15);   
  print_int(list,23);
  printf("\n");
     
  
   
   free_list(&list);  
   list = NULL;
   return EXIT_SUCCESS;
}





