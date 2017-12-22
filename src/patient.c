#include "patient.h"

void patient(MYSQL* connection)
{
  int option;

  printf("1.Dodaj novog pacijenta\n");
  printf("2.Izlistaj podatke o pacijentu i zahvatima\n");
  printf("3.Azuriraj podatke o pacijentu\n");
  printf("4.Obrisi pacijenta\n");
  printf("5.Kraj\n");

  scanf("%d",&option);

  switch (option) {
    case 1:
      addPatient(connection);
      break;
    case 2:
      listPatientCode(connection);
      break;
    case 3:
      updatePatient(connection);
      break;
    case 4:
      deletePatient(connection);
      break;
    case 5:
      exit(EXIT_SUCCESS);
      break;
    default:
      printf("Pogresna opcija\n");
      exit(EXIT_FAILURE);
  }
}

void listPatient(MYSQL* connection)
{
  char query[QUERY_SIZE];
  char name[BUFFER_SIZE];

  printf("\nUnesite ime/prezime pacijenta?\n");
  scanf("%s",name);

  sprintf(query,"select * \
                from Pacijent \
                where Ime like \'%s%%\' or Prezime like \'%s%%\' " ,name,name);

  MYSQL_RES *result = executeQuery(query);

  print(result);
}

void addPatient(MYSQL* connection)
{
  while(1){
    printf("\nZa unos pritisnite u, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    getchar();

    if(strcmp(answer,"n")==0){
      patient(connection);
      break;
    }
    else if(strcmp(answer,"k")==0){
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(answer,"u")==0){
      char Ime[BUFFER_SIZE];
      char Prezime[BUFFER_SIZE];
      char DatumRodjenja[BUFFER_SIZE];
      char Adresa[BUFFER_SIZE];
      char Telefon[BUFFER_SIZE];
      char DatumOtvaranjaKartona[BUFFER_SIZE];

      printf("Unesite ime\n");
      fgets(Ime,BUFFER_SIZE,stdin);
      strtok(Ime,"\n");

      printf("Unesite prezime\n");
      fgets(Prezime,BUFFER_SIZE,stdin);
      strtok(Prezime,"\n");

      printf("Unesite datum rodjenja(GGG-MM-DD)\n");
      scanf("%s",DatumRodjenja);
      getchar();

      printf("Unesite adresu\n");
      fgets(Adresa,BUFFER_SIZE,stdin);
      strtok(Adresa,"\n");

      printf("Unesite telefon\n");
      scanf("%s",Telefon);

      printf("Unesite datum otvaranja kartona(GGG-MM-DD)\n");
      scanf("%s",DatumOtvaranjaKartona);

      sprintf(query,"insert into Pacijent\
                    (idPacijent,Ime,Prezime,DatumRodjenja,Adresa,Telefon,DatumOtvaranjaKartona)\
                    values(0,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",\
                    Ime,Prezime,DatumRodjenja,Adresa,Telefon,DatumOtvaranjaKartona);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}

void listPatientCode(MYSQL* connection)
{
  MYSQL_RES *result;

  listPatient(connection);

  printf("\nOdaberite zeljenog pacijenta(izaberite njegov ID)\n");

  int idPacijent;
  scanf("%d",&idPacijent);

  sprintf(query,"select z.Sifra,z.Datum,p.Ime,p.Prezime,\
                    si.NazivIntervencije,oi.NazivOblasti,\
                    z.Zub,zap.idZaposlenog,zap.Ime\
                from Zahvat z join Pacijent p\
                      on z.idPacijent = p.idPacijent\
                      join SpisakIntervencija si\
                      on z.idSpisak = si.idSpisak\
                      join OblastIntervencije oi\
                      on si.idOblastInt = oi.idOblastInt,\
                      Zaposleni zap\
                where (z.idStomatologa = zap.idZaposlenog or\
                      z.idTehnicara = zap.idZaposlenog) and\
                      z.idPacijent = \'%d\'",idPacijent);

  result = executeQuery(query);

  print(result);

  while(1){
      printf("\nZa unos intervnecije nad izabranim pacijentom pristisnite u, za povratak nazad n, za kraj k\n");

      scanf("%s",answer);
      if(strcmp(answer,"n")==0){
        patient(connection);
        break;
      }
      else if(strcmp(answer,"k")==0){
        exit(EXIT_SUCCESS);
      }
      else if(strcmp(answer,"u")==0){

        sprintf(query,"select * from OblastIntervencije");

        result = executeQuery(query);

        print(result);

        printf("Unesite redni broj oblasti intervencije koju unosite\n");

        int idOblastInt;
        scanf("%d",&idOblastInt);

        sprintf(query,"select * \
                      from SpisakIntervencija \
                      where idOblastInt =\'%d\'",idOblastInt);

        result = executeQuery(query);

        print(result);

        printf("Unesite redni broj intervencije\n");
        int idSpisak;
        scanf("%d",&idSpisak);

        printf("Unesite datum kada je zahvat izvrsen\n");
        char datum[BUFFER_SIZE];
        scanf("%s",datum);

        printf("Unesite zub(1-32) nad kojim je izvrsen zahvat -1, ako je izvrsen nad pokretnim ili fiksnim aparatom\n");
        int Zub;
        scanf("%d",&Zub);

        printf("Unesite ko je izvrsio zahvat(s/t)\n");
        scanf("%s",answer);

        int idZap;

        if(strcmp(answer,"s")==0){

          sprintf(query,"select idZaposlenog,Ime,Prezime \
                        from Zaposleni,Stomatolog\
                        where idZaposlenog = idStomatologa");

          result = executeQuery(query);

          print(result);

          printf("Unesite redni broj stomatologa koji je izvrsio zahvat\n");
          scanf("%d",&idZap);

          sprintf(query,"insert into Zahvat\
                        (Sifra,Datum,Zub,idPacijent,idSpisak,idStomatologa)\
                          values(0,\'%s\',%d,%d,%d,%d)",\
                        datum,Zub,idPacijent,idSpisak,idZap);

          result = executeQuery(query);

          mysql_free_result(result);
        }
        else if(strcmp(answer,"t")==0){

          sprintf(query,"select idZaposlenog,Ime,Prezime \
                        from Zaposleni,Tehnicar\
                        where idZaposlenog = idTehnicara");

          result = executeQuery(query);

          print(result);

          printf("Unesite redBr tehnicara koji je izvrsio zahvat\n");
          scanf("%d",&idZap);

          if(Zub!=-1){
            sprintf(query,"insert into Zahvat\
                          (Sifra,Datum,Zub,idPacijent,idSpisak,idTehnicara)\
                          values(0,\'%s\',%d,%d,%d,%d)",\
                          datum,Zub,idPacijent,idSpisak,idZap);
          }
          else{
            sprintf(query,"insert into Zahvat\
                          (Sifra,Datum,Zub,idPacijent,idSpisak,idTehnicara)\
                          values(0,\'%s\',%s,%d,%d,%d)",\
                          datum,"NULL",idPacijent,idSpisak,idZap);
          }

          result = executeQuery(query);

          mysql_free_result(result);
        }
        else{
            printf("Pogresna komanda\n");
            exit(EXIT_FAILURE);
        }

        printf("\n\nIspis za proveru trigera:\n\n");

        //Ovaj ispis je samo da se vidi da je triger aktiviran
        sprintf(query,"select *\
                      from Pacijent\
                      where idPacijent = \'%d\'",idPacijent);

        result = executeQuery(query);

        print(result);

        //zbog provere trigera je sledeci upit
        sprintf(query,"select * from Stomatolog");

        result = executeQuery(query);

        print(result);

        //zbog provere trigera je sledeci upit
        sprintf(query,"select * from Tehnicar");

        result = executeQuery(query);

        print(result);

      }
    }
}

void updatePatient(MYSQL* connection){

  listPatient(connection);

  printf("Izaberite pacijente,unosom ID-a\n");
  int idPacijent;
  scanf("%d",&idPacijent);

  while(1){
    printf("\nZa izmene pritisnite i, za povratak nazad n, za kraj k\n");

    scanf("%s",answer);
    if(strcmp(answer,"n")==0){
      patient(connection);
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

      sprintf(query,"update Pacijent\
                      set %s=\'%s\'\
                      where idPacijent=%d",column,value,idPacijent);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}

void deletePatient(MYSQL* connection){
  while(1){
    printf("\nZa brisanje pritisnite d, za povratak nazad n, za povratak u glavni meni m\n");

    scanf("%s",answer);
    getchar();
    if(!strcmp(answer,"n")){
      patient(connection);
      break;
    }
    else if(!strcmp(answer,"k")){
      exit(EXIT_SUCCESS);
    }
    else if(!strcmp(answer,"d")){
      listPatient(connection);

      printf("Izaberite pacijente,unosom ID-a\n");
      int idPacijent;
      scanf("%d",&idPacijent);

      sprintf(query,"delete from Pacijent\
                    where idPacijent = %d",idPacijent);

      MYSQL_RES *result = executeQuery(query);

      mysql_free_result(result);
    }
  }
}
