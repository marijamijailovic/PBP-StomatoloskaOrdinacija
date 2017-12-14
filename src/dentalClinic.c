#include "dentalClinic.h"
#include "patient.h"
#include "intervention.h"
#include "material.h"
#include "employees.h"

int main(int argc,char** argv)
{
  int option;

  connection = mysql_init(NULL);

  assert(mysql_real_connect(connection,"localhost","root","","StomatoloskaOrdinacija",0,NULL,0)!=NULL,mysql_error(connection));

  printf("Izaberite opciju:\n");
  printf("1.Podaci o pacijentima\n");
  printf("2.Podaci o intervencijama\n");
  printf("3.Podaci o materijalima\n");
  printf("4.Podaci o zaposlenima\n");
  printf("5.Kraj\n");

  scanf("%d",&option);

  switch (option) {
    case 1:
      patient(connection);
      break;
    case 2:
      intervention(connection);
      break;
    case 3:
      material(connection);
      break;
    case 4:
      employees(connection);
      break;
    case 5:
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("Pogresna opcija\n");
      exit(EXIT_FAILURE);
  }

  mysql_close(connection);

  exit(EXIT_SUCCESS);
}

MYSQL_RES* executeQuery(char* query)
{
  assert(mysql_query(connection,query)==0,\
          mysql_error(connection));
  MYSQL_RES *result = mysql_use_result(connection);
  return result;
}

void print(MYSQL_RES* result)
{

  MYSQL_ROW row;
  MYSQL_FIELD *field;

  field = mysql_fetch_field(result);

  int numOfField = mysql_num_fields(result);

  /*if((row = mysql_fetch_row(result))==NULL){
    printf("Nema zeljenih podataka\n");
    exit(EXIT_FAILURE);
  }*/

  printf("*************************************************\n");
  while((row = mysql_fetch_row(result))!=NULL){
    for(int i=0;i<numOfField;++i){
      printf("%*s:\t%s\n",-25,field[i].name,row[i]);
    }
    printf("------------------------------------------------\n");
  }
  printf("*************************************************\n");

  mysql_free_result(result);
}

void errorFatal(const bool cond,const char* msg,const char* fileName,const int lineNumber)
{
  if(!cond){
    perror(msg);
    fprintf(stderr,"File name:%s\nLine number: %d\n",fileName,lineNumber);
    exit(EXIT_FAILURE);
  }
}
