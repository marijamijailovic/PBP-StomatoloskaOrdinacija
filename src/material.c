#include "material.h"

void material(MYSQL* connection)
{
  int option;

  printf("1.Dodaj Materijal\n");
  printf("2.Izlistaj materijal i intervenciju gde se koristi\n");
  printf("3.Obrisi materijal\n");
  printf("4.Kraj\n");

  scanf("%d",&option);

  switch (option) {
    case 1:
      addMaterial(connection);
      break;
    case 2:
      listMaterial(connection);
      break;
    case 3:
      deleteMaterial(connection);
      break;
    case 4:
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("Pogresna opcija");
      exit(EXIT_FAILURE);
  }
}

void addMaterial(MYSQL* connection)
{
  while(1){
    printf("\nZa unos pritisnite u, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      material(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"u")==0){
      char Naziv[BUFFER_SIZE];

      printf("Unesite naziv materijala\n");
      fgets(Naziv,BUFFER_SIZE,stdin);
      strtok(Naziv,"\n");

      sprintf(query,"insert into Materijal\
                    (idMaterijal,Naziv)\
                    values(0,\'%s\')",\
                    Naziv);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}

void listMaterial(MYSQL* connection)
{
  sprintf(query,"select si.NazivIntervencije,m.Naziv\
                from Koristi k join SpisakIntervencija si\
                    on k.idSpisak = si.idSpisak\
                    join Materijal m\
                    on k.idMaterijal = m.idMaterijal");

  MYSQL_RES *result = executeQuery(query);

  print(result);
}

void deleteMaterial(MYSQL* connection)
{
  MYSQL_RES * result;

  while(1){
    printf("\nZa brisanje pritisnite d, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();
    if(strcmp(answer,"n")==0){
      material(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"d")==0){
      printf("Unesite naziv materijala\n");
      char Naziv[BUFFER_SIZE];
      fgets(Naziv,BUFFER_SIZE,stdin);
      strtok(Naziv,"\n");

      sprintf(query,"select * \
                    from Materijal \
                    where Naziv like \'%s%%\'",Naziv);

      result = executeQuery(query);

      print(result);

      printf("Izaberite ID materijala, koji zelite da obrisete\n");
      int idMaterijal;
      scanf("%d",&idMaterijal);

      sprintf(query,"delete from Materijal\
                    where idMaterijal = %d",idMaterijal);

      result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}
