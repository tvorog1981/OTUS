#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<libpq-fe.h>
#include<math.h>
static void __attribute__ ((noreturn)) finish_with_error(PGconn* conn) {
puts(PQerrorMessage(conn));
PQfinish(conn);
exit(EXIT_FAILURE); }

void close_db(PGconn * conn ,PGresult * res){
  PQclear(res);
  PQfinish(conn);
  res = NULL;
  conn = NULL;
  printf("[ Close connect DB otus ]\n");
}

void avarage_postgres(PGresult *res, int count_row){
  int sum = 0;
  int avr = 0;
  int max = 0;
  int min = 0;
  double dis;
  for(int i = 0 ; i < count_row;i++){
    char* id = PQgetvalue(res, i, 0);
    int rez =  strtol(id, (char **)NULL, 10);
    if(i == 0){
      min = max = rez;
    }else{
      if(min > rez){
	min = rez;
      }
      if(max < rez){
	max = rez;
      }
    }
    sum += rez;
    avr += 1;
    printf("%d\n",rez);
  }
 int a = sum /avr;
  for(int i = 0 ; i < count_row;i++){
        char* id = PQgetvalue(res, i, 0);
    int rez =  strtol(id, (char **)NULL, 10);
    dis +=( (rez - a) * (rez - a));


  }
  

  printf("sum => %d avr => %d  max => %d min => %d dispersia => %lf \n",sum, a,max,min,(dis / count_row));
}

int main(int argc ,char ** argv){
  if(argc < 4 || argc > 4){
    printf("you want %s <namedb> <tablename> <name col>\n",argv[0]);
    exit(-1);
    
  }
  
  char buff_connect[255];
  char buff_host[50];
  char buff_port[50];
  char buff_user[50];
  char buff_dbname[50];
  char buff_passwd[50];
  
  bzero(buff_host,50);
  bzero(buff_port,50);
  bzero(buff_user,50);
  bzero(buff_dbname,50);
  bzero(buff_passwd,50);
  
   strncpy(buff_host,"localhost",strlen("localhost"));
   strncpy(buff_port,"5432",strlen("5432"));
   strncpy(buff_user,"otus",strlen("otus"));
   strncpy(buff_passwd,"Tvorog1981",strlen("Tvorog1981"));
   strncpy(buff_dbname,argv[1],strlen(argv[1]));

     //strncpy(buff_host,"localhost",strlen("localhost"));
  
  sprintf(buff_connect,"host=%s port=%s user=%s dbname=%s password=%s",buff_host,buff_port,buff_user,buff_dbname,buff_passwd);

  // printf("%s\n\n",buff_connect);
  //PGconn * conn = PQconnectdb("host=localhost port=5432 user=otus dbname=otus password=Tvorog1981");

  PGconn * conn = PQconnectdb(buff_connect);
  if(PQstatus(conn) != CONNECTION_OK){
    finish_with_error(conn);

  }else{
    printf("[ Connect DB Postgres ]\n");
  }


  PGresult * res = NULL;
  char exec_string[255];
  bzero(exec_string,255);

  sprintf(exec_string,"SELECT %s FROM %s",argv[3],argv[2]);

         // res = PQexec(conn,"SELECT  FROM oscar");
	   res = PQexec(conn,exec_string);

  if(PQresultStatus(res) != PGRES_TUPLES_OK){
        finish_with_error(conn);
  }
  
  //int count_cols = PQnfields(res);
  //for(int i = 0 ; i < count_cols; i++){
     //if(i == 0){printf(" | ");}
   // char * name_field = PQfname(res,i);
    // printf(" %s ",name_field);
    // printf(" | ");
    // }
   // printf("\n");
  int count_row = PQntuples(res);
  //for(int j = 0 ; j <  count_row;j++){
     // char* id = PQgetvalue(res, j, 0);
  // char* year = PQgetvalue(res, j, 1);
  // char* age = PQgetvalue(res, j, 2);
  // char* name = PQgetvalue(res, j, 3);
  // char* movie = PQgetvalue(res, j, 4);
  // printf("%s %s %s %s %s\n", id, year, age, name, movie);
     // printf("%s\n", id);   

     // }
   // printf("\n");
 avarage_postgres(res,count_row);
  close_db(conn,res);
  return EXIT_SUCCESS;
}
