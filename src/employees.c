#include "employees.h"

void employees(MYSQL* connection)
{
  listEmployees(connection);

  int option;

  printf("1.Dodaj zaposlenog\n");
  printf("2.Azuriraj podatke o zaposlenom\n");
  printf("3.Obrisi zaposlenog\n");
  printf("4.Kraj\n");

  scanf("%d",&option);

  switch (option) {
    case 1:
      addEmployees(connection);
      break;
    case 2:
      updateEmployees(connection);
      break;
    case 3:
      deleteEmployees(connection);
      break;
    case 4:
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("Pogresna opcija");
      exit(EXIT_FAILURE);
  }
}

void listEmployees(MYSQL* connection)
{
  char query[QUERY_SIZE];
  char name[BUFFER_SIZE];

  sprintf(query,"select *\
                from Zaposleni");

  MYSQL_RES *result = executeQuery(query);

  print(result);
}

void addEmployees(MYSQL* connection)
{
  MYSQL_RES* result;

  while(1){
    printf("\nZa unos pritisnite u, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      employees(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"u")==0){
      char Ime[BUFFER_SIZE];
      char Prezime[BUFFER_SIZE];

      printf("Unesite ime zaposlenog\n");
      fgets(Ime,BUFFER_SIZE,stdin);
      strtok(Ime,"\n");

      printf("Unesite prezime zaposlenog\n");
      fgets(Prezime,BUFFER_SIZE,stdin);
      strtok(Prezime,"\n");

      sprintf(query,"insert into Zaposleni\
                    (idZaposlenog,Ime,Prezime)\
                    values(0,\'%s\',\'%s\')",\
                    Ime,Prezime);

      result = executeQuery(query);

      mysql_free_result(result);

      sprintf(query,"select max(idZaposlenog)\
                    from Zaposleni");

      result = executeQuery(query);

      MYSQL_ROW row = mysql_fetch_row(result);

      int idZaposlenog = atoi(row[0]);

      mysql_free_result(result);

      printf("Da li zaposleni stomatolog ili tehnicar(s/t)\n");
      scanf("%s",answer);
      getchar();

      if(strcmp(answer,"s")==0){
        printf("Unesite status zaposlenom(stalan radni odnos/praksa/probni rad)\n");
        char Status[BUFFER_SIZE];
        fgets(Status,BUFFER_SIZE,stdin);
        strtok(Status,"\n");

        printf("Unesite radno iskustvo zaposlenog(0-100)\n");
        int RadnoIskustvo;
        scanf("%d",&RadnoIskustvo);

        sprintf(query,"insert into Stomatolog\
                      values(%d,\'%s\',%d)",\
                      idZaposlenog,Status,RadnoIskustvo);

        result = executeQuery(query);

        mysql_free_result(result);
      }
      else{
        printf("Unesite radno iskustvo zaposlenog(0-100)\n");
        int RadnoIskustvo;
        scanf("%d",&RadnoIskustvo);

        sprintf(query,"insert into Tehnicar\
                      values(%d,%d)",\
                      idZaposlenog,RadnoIskustvo);

        result = executeQuery(query);

        mysql_free_result(result);
      }
    }
  }
}

void updateEmployees(MYSQL* connection)
{
  while(1){
    printf("\nZa izmene pritisnite i, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    if(strcmp(answer,"n")==0){
      employees(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"i")==0){
      printf("Izaberite zaposlenog,unosom ID-a\n");
      int idZaposlenog;
      scanf("%d",&idZaposlenog);

      printf("Unesite ime kolone koju zelite da izmenite\n");
      char column[BUFFER_SIZE];
      scanf("%s",column);
      getchar();

      printf("Unesite novi podatak\n");
      char value[BUFFER_SIZE];
      fgets(value,BUFFER_SIZE,stdin);
      strtok(value,"\n");

      if(strcasecmp(column,"Status")==0){
        sprintf(query,"update Stomatolog\
                        set %s=\'%s\'\
                        where idStomatologa=%d",column,value,idZaposlenog);

        MYSQL_RES *result = executeQuery(query);

        mysql_free_result(result);
      }
      else{
        sprintf(query,"update Zaposleni\
                        set %s=\'%s\'\
                        where idZaposlenog=%d",column,value,idZaposlenog);

        MYSQL_RES *result = executeQuery(query);

        mysql_free_result(result);
      }
    }
  }
}

void deleteEmployees(MYSQL* connection)
{
  while(1){
    printf("\nZa brisanje pritisnite d, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      employees(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"d")==0){
      printf("Izaberite zaposlenog,unosom ID-a\n");
      int idZaposlenog;
      scanf("%d",&idZaposlenog);

      sprintf(query,"delete from Zaposleni\
                    where idZaposlenog = %d",idZaposlenog);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}
