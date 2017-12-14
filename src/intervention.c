#include "intervention.h"

void intervention(MYSQL* connection)
{
  int idOblasti = listDentalCode(connection);

  int option;

  printf("1.Dodaj intervenciju\n");
  printf("2.Azuriraj intervenciju\n");
  printf("3.Obrisi intervenciju\n");
  printf("4.Kraj\n");

  scanf("%d",&option);

  switch (option) {
    case 1:
      addIntervention(connection,idOblasti);
      break;
    case 2:
      updateIntervention(connection);
      break;
    case 3:
      deleteInterention(connection);
      break;
    case 4:
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("Pogresna opcija");
      exit(EXIT_FAILURE);
  }
}

void listDentalWork(MYSQL* connection)
{
  char query[QUERY_SIZE];

  sprintf(query,"select * \
                from OblastIntervencije");

  MYSQL_RES *result = executeQuery(query);

  print(result);
}

int listDentalCode(MYSQL* connection)
{
  listDentalWork(connection);

  printf("\nOdaberite zeljenu oblas(izaberite ID)\n");
  int idOblastInt;
  scanf("%d",&idOblastInt);

  sprintf(query,"select *\
                from SpisakIntervencija\
                where idOblastInt=%d",idOblastInt);

  MYSQL_RES *result = executeQuery(query);

  print(result);

  return idOblastInt;
}

void addIntervention(MYSQL* connection,int idOblasti)
{
  while(1){
    printf("\nZa unos pritisnite u, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      intervention(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"u")==0){
      char NazivIntervencije[BUFFER_SIZE];
      int Cena;

      printf("Unesite naziv intervencije\n");
      fgets(NazivIntervencije,BUFFER_SIZE,stdin);
      strtok(NazivIntervencije,"\n");

      printf("Unesite cenu\n");
      scanf("%d",&Cena);

      sprintf(query,"insert into SpisakIntervencija\
                    (idSpisak,NazivIntervencije,Cena,idOblastInt)\
                    values(0,\'%s\',%d,%d)",\
                    NazivIntervencije,Cena,idOblasti);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}

void updateIntervention(MYSQL* connection)
{
  while(1){
    printf("\nZa izmene pritisnite i, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    if(strcmp(answer,"n")==0){
      intervention(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"i")==0){
      printf("Unesite ime kolone koju zelite da izmenite\n");
      char column[BUFFER_SIZE];
      scanf("%s",column);
      getchar();
      printf("Unesite novi podatak\n");
      char value[BUFFER_SIZE];
      if(fgets(value,BUFFER_SIZE,stdin)!=NULL){
        strtok(value,"\n");
      }
      printf("Unesite ID spiska\n");
      int idSpisak;
      scanf("%d",&idSpisak);

      sprintf(query,"update SpisakIntervencija\
                      set %s=\'%s\'\
                      where idSpisak=%d",column,value,idSpisak);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}

void deleteInterention(MYSQL* connection)
{
  while(1){
    printf("\nZa brisanje pritisnite d, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      intervention(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"d")==0){
      printf("Unesite ID spiska\n");
      int idSpisak;
      scanf("%d",&idSpisak);

      sprintf(query,"delete from SpisakIntervencija\
                    where idSpisak = %d",idSpisak);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}
