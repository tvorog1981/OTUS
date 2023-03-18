#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<curl/curl.h>
#include<cjson/cJSON.h>



/* struct for json */
typedef struct _JSON_DATA_ JSON_DATA;

struct _JSON_DATA_ {
  cJSON * temp_c;
  cJSON * temp_f;
  cJSON *city;
  cJSON * country;
  cJSON * wind_speed;
  cJSON * wind_direction;
  cJSON * localdata;


};



/* struct for curl data */
typedef struct _Parsing Parsing;

struct _Parsing{
  char * response;
  size_t len;
  
};


/* parsing json strings */
int weather_json(const char * const  w){
  //  printf("%s",w);
  int status = 0;
  cJSON * json = cJSON_Parse(w);

  if(json  == NULL){
    printf("Error \n");
    const char * err = cJSON_GetErrorPtr();
    if(err != NULL){
      fprintf(stderr,"Error parse %s\n",err);

    }
    status = 0;
    goto end;

  }
  
  const cJSON * current_condition = NULL;
  const cJSON * array_weather = NULL;
  JSON_DATA json_data;



  current_condition = cJSON_GetObjectItemCaseSensitive( json, "current_condition");

 

             


  cJSON_ArrayForEach( array_weather, current_condition ){
   json_data.wind_speed =  cJSON_GetObjectItemCaseSensitive( array_weather, "windspeedKmph");
         json_data.localdata = cJSON_GetObjectItemCaseSensitive(array_weather, "localObsDateTime");
	          json_data.wind_direction = cJSON_GetObjectItemCaseSensitive(array_weather, "winddir16Point");
	  //printf("%s",json_data.wind_speed->valuestring);
	 //cJSON * observation_time = cJSON_GetObjectItemCaseSensitive(array_weather, "observation_time");
         json_data.temp_c = cJSON_GetObjectItemCaseSensitive(array_weather, "temp_C");
	 json_data.temp_f = cJSON_GetObjectItemCaseSensitive(array_weather, "temp_F");
             }




  /* city country parsing */
  cJSON * array_city_country;
  cJSON * nearest_area =cJSON_GetObjectItemCaseSensitive( json, "nearest_area");

  cJSON_ArrayForEach( array_city_country, nearest_area ){

      cJSON * areaName = cJSON_GetObjectItemCaseSensitive(array_city_country, "areaName");   
      cJSON * arrCity;
     cJSON_ArrayForEach( arrCity, areaName ){
     json_data.city  = cJSON_GetObjectItemCaseSensitive(arrCity, "value");
       //cJSON * c = cJSON_GetObjectItemCaseSensitive(arrCity, "value");
     // printf("%s",c->valuestring);
     }
   

     cJSON * country = cJSON_GetObjectItemCaseSensitive(array_city_country, "country");
      cJSON * arrCountry;
     cJSON_ArrayForEach( arrCountry, country ){
          json_data.country  = cJSON_GetObjectItemCaseSensitive(arrCountry, "value");
       //    cJSON * c = cJSON_GetObjectItemCaseSensitive(arrCountry, "value");
       //printf("%s",c->valuestring);
	  //        printf("%s",json_data.country->valuestring);
     }
 }





 
  /* print data */
    printf(" _______________________________________________________________________________________________________________________ ");
    printf(" \n|country %s | city %s |data %s | temp C %s | temp F %s |speed wind %sk/h | wind direction %s |\n",json_data.country->valuestring, json_data.city->valuestring,json_data.localdata->valuestring,json_data.temp_c->valuestring ,json_data.temp_f->valuestring,json_data.wind_speed->valuestring,json_data.wind_direction->valuestring);
   printf ("________________________________________________________________________________________________________________________\n ");
 
  


  //cJSON * localObsDateTime = cJSON_GetObjectItemCaseSensitive(array_weather, "localObsDateTime");
  // printf("%s",localObsDateTime->valuestring);
  // astronomy = cJSON_GetObjectItemCaseSensitive( weather, "astronomy");
  //  printf("->%s",weather->valuestring);

 end:
  cJSON_Delete(json);
  return status;
}










/* parsing response from server */
size_t response_from_server(void * data, size_t size_first, size_t size_second  , void * server){

  size_t real_size = size_first * size_second;
  //    printf( "first size -> %zu second size %zu real size %zu ",size_first ,size_second ,real_size );

  Parsing * res = (Parsing *)server;
  res->response = (char *)realloc( res->response ,  res->len + real_size + 1);

  if(res->response == NULL){
    printf("calloc faild \n");
    return 0;
  }

  
  memcpy(res->response+ res->len , data, real_size + 1);

  res->len += real_size;

  res->response[res->len] = 0;
  
  // printf("%s",(char * )data);

  
  return real_size;
}









/* parsing url string */
char * url_parsing(char * first){
  if(strlen(first) == 0)
    {
      exit(1);
    }
  
  char * main = "https://wttr.in/"; 
 
  char * second  = "?format=j1";
  int full_size = strlen(main) + strlen(first) + strlen(second) ;

  char * real_path = (char *) malloc(full_size + 1);

  /* check allocate memory */
  if(real_path == NULL){
    exit(1);
  }
  // bzero(&real_path,sizeof(real_path));













  /* create string url */
  memcpy(real_path, main, strlen(main));
    
  memcpy(real_path + strlen(main), first, strlen(first));
 
  memcpy(real_path + strlen(main) + strlen(first), second, strlen(second));

  real_path[full_size] = 0;

  //  printf("++++++++++%s+++++++++++",real_path);
  return  real_path;
}


/* main function */
int main(int argc , char ** argv){

  /* check arguments command line */
  if(argc  < 2 || argc > 2){
    printf(" %s <city> \n",argv[0]);
    exit(1);
  }





  Parsing server ={0};

  CURL * curl;
  CURLcode response;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  // char * url_path = "https://google.ru";
  /* check on created curl */
  if(curl){
    // struct curl_slist * header = NULL;
    char * url_path = url_parsing(argv[1]);


    //   curl_slist_append(header,"Accept: application/json");

    /* options curl and header */
    curl_easy_setopt(curl,CURLOPT_URL,url_path);
    //     curl_easy_setopt(curl,CURLOPT_HTTPHEADER,header);
     curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0L);
     curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,response_from_server);
     curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void *)&server);
    

    response = curl_easy_perform(curl);
    
    /* status response from server bad */
    if(response != CURLE_OK){
      free(url_path);
      free(server.response);
      fprintf(stderr,"faild %s \n",curl_easy_strerror(response));
    }
    
    // printf("%s" ,server.response);


    /* status response from server OK */
    if(response == CURLE_OK){
      weather_json((const  char *  const)server.response);   
      free(server.response);
      free(url_path);
    }	
    curl_easy_cleanup(curl);
    // free(header);    
  }


   
  curl_global_cleanup();

  return EXIT_SUCCESS;
}

