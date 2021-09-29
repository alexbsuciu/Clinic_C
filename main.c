#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")

FILE* f;
char citire[501];
int ctMedic;
int ctProgramari;
int alegere, alegeredoc, alegerepr; //variabile pt switchuri
char yes[50] = "pentru luci de la pufel";
// --------------Aici partea de cod pentru doctori--------------

struct medic
{
	char *nume;
	char *prenume;
	char *CNP;
	char *specializare;
}medic[1000];

struct medic createMedic(char *num, char *pren, char *cnp, char *spec)
{     //Lucian Streulea
  struct medic m;
  m.nume = malloc(sizeof(num));
  strcpy(m.nume, num);
  m.prenume = malloc(sizeof(pren));
  strcpy(m.prenume, pren);
  m.CNP = malloc(sizeof(cnp));
  strcpy(m.CNP, cnp);
  m.specializare = malloc(sizeof(spec));
  strcpy(m.specializare, spec);
  return m;
}

void citireMedici()
{         // Stan Mihnea Claudiu
  ctMedic = 0;
  f = fopen("doctori.txt", "r");
  while (fgets(citire, 500, f))
    {
	    char *num, *pren, *cnp, *spec;
	    num = strtok(citire,",");
      pren = strtok(NULL,",");
	    cnp = strtok(NULL,",");
      spec = strtok(NULL,",");
	    medic[ctMedic] = createMedic(num, pren, cnp, spec);
      ctMedic++;
    }
	fclose(f);
}

void afisareMedici()
{         // Stan Mihnea Claudiu
  printf("Nr.  Nume  Prenume  CNP  Specializare\n");

	for(int i = 0; i < ctMedic; i++)
		printf("[%d] %s %s %s %s", i+1, medic[i].nume, medic[i].prenume, medic[i].CNP, medic[i].specializare);
}

void addMedic()
{
    //Lucian Streulea
	char num[20], pren[20], cnp[20], spec[50];
	printf(" Numele doctorului: ");
	scanf("%s", num);
	for(int i = 0; i < strlen(num); i++)
		num[i] = tolower(num[i]);
	printf(" Prenumele doctorului: ");
	scanf("%s", pren);
	for(int i = 0; i < strlen(pren); i++)
		pren[i] = tolower(pren[i]);
	printf(" CNP-ul doctorului: ");
	scanf("%s", cnp);
	printf(" Specializarea doctorului: ");
	scanf("%s", spec);
	for(int i = 0; i < strlen(spec); i++)
		spec[i] = tolower(spec[i]);
  strcat(spec,"\n");
	medic[ctMedic] = createMedic(num, pren, cnp, spec);
	ctMedic++;
}

void sortareMedici()
{         // Stan Mihnea Claudiu
  for(int i=0; i<ctMedic-1; i++)
  {
    for(int j=i+1; j<ctMedic; j++)
    {
      if(strcmp(medic[i].nume, medic[j].nume)>0)
      {
        struct medic aux = medic[i];
        medic[i] = medic[j];
        medic[j] = aux;
      }
      else
      {
        if(strcmp(medic[i].nume, medic[j].nume)==0)
        {
          if(strcmp(medic[i].prenume, medic[j].prenume)>0)
          {
           struct medic aux = medic[i];
           medic[i] = medic[j];
           medic[j] = aux;
          }
        }
      }
    }
  }
}

int cautareMedic()
{
  // Suciu Alexandru
	int index = - 1;
	printf(" Introduceti CNP-ul medicului cautat: ");
	char cnp[15];
	scanf("%s", cnp);
	for(int i = 0; i < ctMedic; i++)
		if(strcmp(medic[i].CNP, cnp) == 0)
		{
			index = i;
			break;
		}
	return index;
}

void modificareMedic()
{
  // Suciu Alexandru
	int indexProg = cautareMedic();
  if(indexProg == -1)
  {
    printf("CNP-ul introdus nu a fost gasit in baza de date!");
  }
  else
  {
    int algMod = 0;
	printf(" Ce doriti sa modificati? \n");
	printf("1) Numele\n");
	printf("2) Prenumele\n");
	printf("3) CNP\n");
	printf("4) Specializarea\n");
	printf(" Introduceti optiunea: ");
	scanf("%d", &algMod);
	char modificare[100];
	switch(algMod)
	{
		case 1: 
		printf(" Numele nou: ");
		scanf("%s", modificare);
		strcpy(medic[indexProg].nume, modificare);
		break;

		case 2: 
		printf(" Prenumele nou: ");
		scanf("%s", modificare);
		strcpy(medic[indexProg].prenume, modificare);
		break;

		case 3: 
		printf(" CNP-ul nou: ");
		scanf("%s", modificare);
		strcpy(medic[indexProg].CNP, modificare);
		break;

		case 4: 
		printf(" Specializare noua: ");
		scanf("%s", modificare);
		strcpy(medic[indexProg].specializare, modificare);
    strcat(medic[indexProg].specializare,"\n");
		break;
		
		default: break;		
	}
  }
	
}

void stergereMedic(int pozitie)
{     // Suciu Alexandru
  if(pozitie == -1)
  {
    printf("Medic inexistent.\n");
    return;
  }
  for(int i=pozitie;i<ctMedic-1;i++)
  {
    struct medic aux;
    aux = medic[i+1];
    medic[i] = aux;
  }
  ctMedic--;
}

void cautareSpecializare(char *s)
{     //Suciu Alexandru
  int afisare = 0;
  for(int i=0;i<ctMedic;i++)
  {
    if(strstr(medic[i].specializare,s))
    {
      afisare = 1;
      printf("[%d] %s %s %s %s", i+1, medic[i].nume, medic[i].prenume, medic[i].CNP, medic[i].specializare);
    }
  }
  if(afisare == 0)
    printf(" Nu exista medic cu specializarea de %s", s);
}

void updatareMedici()
{       // Suciu Alexandru
  // rescrie baza de date in fisier cu modificarile efectuate
  f = fopen("doctori.txt", "w+");
  for(int i=0;i<ctMedic;i++)
  {
      fprintf(f,"%s,%s,%s,%s", medic[i].nume, medic[i].prenume, medic[i].CNP, medic[i].specializare);
  }
  fclose(f);
}

// --------------Aici partea de cod pentru programari--------------

struct pacient
{
  char *nume;
  char *prenume;
  char *CNP;
  char *trimitere;
  char *data;
  char *clinica;
}programare[1000];

struct pacient createProgramare(char *num, char *pren, char *cnp, char *trim, char *data, char *clin)
{
  //Lucian Streulea
  struct pacient p;
  p.nume = malloc(sizeof(num));
  strcpy(p.nume, num);
	p.prenume = malloc(sizeof(pren));
  strcpy(p.prenume, pren);
  p.CNP = malloc(sizeof(cnp));
  strcpy(p.CNP, cnp);
  p.trimitere = malloc(sizeof(trim));
  strcpy(p.trimitere, trim);
  p.data = malloc(sizeof(data));
  strcpy(p.data, data);
  p.clinica = malloc(sizeof(clin));
  strcpy(p.clinica, clin);
  return p;
}

void citireProgramari()
{     // Stoia Teodora
  ctProgramari = 0;
  f = fopen("programari.txt", "r");
  while (fgets(citire, 500, f))
    {
	    char *num, *pren, *cnp, *trim, *data, *clin;
	    num = strtok(citire,",");
  	  pren = strtok(NULL,",");
	    cnp = strtok(NULL,",");
	    trim = strtok(NULL,",");
	    data = strtok(NULL,",");
	    clin = strtok(NULL,",");
	    programare[ctProgramari] = createProgramare(num, pren, cnp, trim, data, clin);
			ctProgramari++;
    }
	fclose(f);
}

void afisareProgramari()
{     // Stoia Teodora
  printf("Nr.  Nume   Prenume    CNP   Trimitere    Data      Clinica\n");

	for(int i = 0; i < ctProgramari; i++)
		printf("[%d] %s %s %s %s %s %s", i+1, programare[i].nume, programare[i].prenume, programare[i].CNP, programare[i].trimitere, programare[i].data, programare[i].clinica);
}

void addProgramare()
{
  //Lucian Streulea
	char num[20], pren[20], cnp[20], trimitere[20], data[20], clin[50];
	printf(" Numele pacientului: ");
	scanf("%s", num);
	for(int i = 0; i < strlen(num); i++)
		num[i] = tolower(num[i]);
	printf(" Prenumele pacientului: ");
	scanf("%s", pren);
	for(int i = 0; i < strlen(pren); i++)
		pren[i] = tolower(pren[i]);
	printf(" CNP-ul pacientului: ");
	scanf("%s", cnp);
	printf(" Pacientul are trimitere: ");
	scanf("%s", trimitere);
	for(int i = 0; i < strlen(trimitere); i++)
		trimitere[i] = tolower(trimitere[i]);
	printf(" Data programarii: ");
	scanf("%s", data);
	printf(" Clinica pacientului: ");
	scanf("%s", clin);
	for(int i = 0; i < strlen(clin); i++)
		clin[i] = tolower(clin[i]);
	strcat(clin, "\n");
	programare[ctProgramari] = createProgramare(num, pren, cnp, trimitere, data, clin);
  ctProgramari++;
}

int verificareData(char *data1, char *data2);

void sortareProgramari()
{     // Stoia Teodora
  for(int i=0; i<ctProgramari-1; i++)
  {
    for(int j=i+1; j<ctProgramari; j++)
    {
      if(verificareData(programare[i].data, programare[j].data))
      {
        struct pacient aux = programare[i];
        programare[i] = programare[j];
        programare[j] = aux;
      }
    }
  }
}

int cautareProgramare()
{
  //Lucian Streulea
	int index = - 1;
	printf(" Introduceti CNP-ul pacientului cautat: ");
	char cnp[15];
	scanf("%s", cnp);
	for(int i = 0; i < ctProgramari; i++)
		if(strcmp(programare[i].CNP, cnp) == 0)
			index = i;
	return index;
}


void afisareProgramare(struct pacient p, int i)
{
  //Lucian Streulea
  printf("[%d] %s %s %s %s %s %s", i + 1, p.nume, p.prenume, p.CNP, p.trimitere, p.data, p.clinica);
}

void searchByClin()
{  //Stan Claudiu Mihnea
  int afisare = 0;
  printf(" Introduceti clinica:");
  char *clin = malloc(50 * sizeof(char));
  scanf("%s", clin);
  for(int i = 0; i < ctProgramari; i++)
    if(strstr(programare[i].clinica, clin))
    {
      afisareProgramare(programare[i], i);
      afisare = 1;
    }
  if(afisare == 0)
    printf(" Nu exista programari la clinica de %s", clin);
}

void searchByDate()
{ // Stoia Teodora
  int afisare = 0;
  printf(" Introduceti data:");
  char *data = malloc(12 * sizeof(char));
  scanf("%s", data);
  for(int i = 0; i < ctProgramari; i++)
    if(strstr(programare[i].data, data))
    {
      afisareProgramare(programare[i], i);
      afisare = 1;
    }
  if(afisare == 0)
    printf(" Nu exista programari in data %s", data);
}

void stergereProgramare(int pozitie)
{       // Suciu Alexandru
  for(int i = pozitie; i < ctProgramari - 1; i++)
  {
    struct pacient aux;
    aux = programare[i+1];
    programare[i] = aux;
  }
  ctProgramari--;
}

void modificareProgramare()
{
  //Lucian Streulea
	int indexProg = cautareProgramare();
  if(indexProg==-1)
  {
    printf("CNP-ul introdus nu a fost gasit in baza de date!");
  }
  else
  {
    int algMod = 0;
	printf(" Ce doriti sa modificati? \n");
	printf("1) Numele\n");
	printf("2) Prenumele\n");
	printf("3) CNP\n");
	printf("4) Trimitere\n");
	printf("5) Data\n");
	printf("6) Clinica\n");
	printf(" Introduceti optiunea: ");
	scanf("%d", &algMod);
	char modificare[100];
	switch(algMod)
	{
		case 1: 
		printf(" Numele nou: ");
		scanf("%s", modificare);
		strcpy(programare[indexProg].nume, modificare);
		break;

		case 2: 
		printf(" Prenumele nou: ");
		scanf("%s", modificare);
		strcpy(programare[indexProg].prenume, modificare);
		break;

		case 3: 
		printf(" CNP-ul nou: ");
		scanf("%s", modificare);
		strcpy(programare[indexProg].CNP, modificare);
		break;

		case 4: 
		printf(" Trimtere noua: ");
		scanf("%s", modificare);
		strcpy(programare[indexProg].trimitere, modificare);
		break;

		case 5: 
		printf(" Data noua: ");
		scanf("%s", modificare);
		strcpy(programare[indexProg].data, modificare);
		break;

		case 6: 
		printf(" Clinica noua: ");
		scanf("%s", modificare);    
		strcpy(programare[indexProg].clinica, modificare);
    strcat(programare[indexProg].clinica, "\n");
		break;
		
		default: break;		
  }
	
	}
}

char *getDate();

void searchProgByDate()
{
  int afisare = 0;
  //Lucian Streulea
  char *data = getDate();
  for(int i = 0; i < ctProgramari; i++)
    if(verificareData(programare[i].data, data))
      {
        afisare = 1;
        afisareProgramare(programare[i], i);
      }
  if(afisare == 0)
    printf(" Nu exista programare in data de azi!");
}

void updatareProgramari()
{       // Suciu Alexandru
    // rescrie baza de date in fisier cu modificarile efectuate
  f = fopen("programari.txt", "w+");
  for(int i=0;i<ctProgramari;i++)
  {
      fprintf(f,"%s,%s,%s,%s,%s,%s", programare[i].nume, programare[i].prenume, programare[i].CNP, programare[i].trimitere, programare[i].data, programare[i].clinica);
  }
  fclose(f);
}

// --------------Main si alte functii--------------

char *getDate()
{   //Lucian Streulea
  char *date = malloc(12 * sizeof(char));
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  int day = local->tm_mday;
  int month = local->tm_mon + 1;
  int year = local->tm_year + 1900;
  char buff[10];
  sprintf(buff, "%d", day);
  strcpy(date, buff);
  strcat(date, "/");
  if(month < 10)
    strcat(date, "0");
  sprintf(buff, "%d", month);
  strcat(date, buff);
  strcat(date, "/");
  sprintf(buff, "%d", year);
  strcat(date, buff);
  return date;
}

int getDay(char *date)
{
    int day = 0;
    for(int i = 0; i < 2; i++)
        day = day * 10 + (date[i] - '0');
    return day;
}

int getMonth(char *date)
{
    int month = 0;
    for(int i = 3; i < 5; i++)
        month = month * 10 + (date[i] - '0');
    return month;
}

int getYear(char *date)
{
    int year = 0;
    for(int i = 6; i < strlen(date); i++)
        year = year * 10 + (date[i] - '0');
    return year;
}

int verificareData(char *data1, char *data2)
{
           //Lucian Streulea
    int day1 = getDay(data1), month1 = getMonth(data1), year1 = getYear(data1);
    int day2 = getDay(data2), month2 = getMonth(data2), year2 = getYear(data2);
    if(year1 > year2)
        return 1;
    else if(year1 < year2)
        return 0;
    else
    {
        if(month1 > month2)
            return 1;
        else if(month1 < month2)
            return 0;
        else
        {
            if(day1 > day2)
                return 1;
            else if(day1 == day2)
                return 1;
            else
                return 0;
            return 0;
        }
        return 0;
    }
}

void endTask()
{ // Suciu Alexandru
  printf("\n");
  printf("\n");
  printf("Comanda finalizata!\n");
  printf("1) Inapoi la meniu\n");
  printf("Apasati orice alt numar pentru inchiderea programului!\n");
}

int main(void) 
{

  // Suciu Alexandru

  clrscr();
  printf("Selectati cifra corenspunzatoare optiunii dorite:\n");
  optiuni1: 
  printf("1) Baza de date pentru doctori\n");
  printf("2) Baza de date pentru programari\n");
  printf("0) Inchidere\n");
  scanf("%d",&alegere);
  switch(alegere)
  {
    case 1:
    {
      //baza de date pentru doctori
			citireMedici();
      clrscr();
      printf("Alegeti actiunea dorita:\n");
      optiunidoctori:
      printf("1) Afisare lista doctori\n");
      printf("2) Adaugarea unui doctor nou\n");
      printf("3) Stergerea unui doctor din lista\n");
      printf("4) Modificarea datelor unui doctor\n");
      printf("5) Afisarea doctorilor cu o anumita specialitate\n");
      printf("0) Inapoi\n");
      scanf("%d",&alegeredoc);
      switch(alegeredoc)
      {
        case 1:
        {
          // afisare doctori
          clrscr();
          sortareMedici();
          afisareMedici();
          updatareMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 2:
        {
          // adaugare doctori
          clrscr();
          addMedic();
          sortareMedici();
          updatareMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 3:
        {
          // stergere doctor
          clrscr();
          stergereMedic(cautareMedic());
          sortareMedici();
          updatareMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 4:
        {
          // modificare doctor
          clrscr();
          modificareMedic();
          sortareMedici();
          updatareMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 5:
        {
          clrscr();
          printf("Introduceti specializarea:\n");
          char spec[100];
          scanf("%s",spec);
          cautareSpecializare(spec);
          sortareMedici();
          updatareMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 0:
        {
          clrscr();
          printf("Alegeti o optiune:\n");
          goto optiuni1;
        }
        default:
        {
          clrscr();
          printf("Alegere invalida, va rugam incercati din nou!\n");
          goto optiunidoctori;
        }
      }
      break;
    }
    case 2:
    {
      //baza de date pentru programari
			citireProgramari();
      clrscr();
			optiuniprogramari:
      printf("1) Afisare lista programari\n");
      printf("2) Adaugarea unei programari noi\n");
      printf("3) Stergerea unei programari din lista\n");
      printf("4) Modificarea datelor unei programari\n");
      printf("5) Afisarea programarilor de azi\n");
      printf("6) Afisarea programarilor dintr-o anumita data\n");
      printf("7) Afisarea programarilor de la o anumita clinica\n");
      printf("0) Inapoi\n");
      scanf("%d",&alegerepr);
      switch(alegerepr)
      {
        case 1:
        {
          // afisare programari
          clrscr();
          sortareProgramari();
          afisareProgramari();
          updatareProgramari();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 2:
        {
          // adaugare programari
          clrscr();
          addProgramare();
          sortareProgramari();
          updatareProgramari();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 3:
        {
          // stergere programare
          clrscr();
          stergereProgramare(cautareProgramare());
          sortareProgramari();
          updatareProgramari();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 4:
        {
          // modificare programare
          clrscr();
          modificareProgramare();
          sortareProgramari();
          updatareProgramari();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 5:
        {
          clrscr();
          searchProgByDate();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 6:
        {
          clrscr();
          searchByDate();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 7:
        {
          clrscr();
          searchByClin();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 0:
        {
          clrscr();
          printf("Alegeti o optiune:\n");
          goto optiuni1;
        }
        default:
        {
          clrscr();
          printf("Alegere invalida, va rugam incercati din nou!\n");
          goto optiuniprogramari;
        }
      }
      break;
    }
    case 0:
    {
      return 0;
    }
    default:
    {
      clrscr();
      printf("Alegere invalida, va rugam incercati din nou!\n");
      goto optiuni1;
    }
  }
  return 0;
}