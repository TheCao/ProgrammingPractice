/*
 * main.c
 *
 *  Created on: 25.10.2016
 *      Author: cao
 *      Operacje na strukturach + dynamiczne alokowanie tablicy struktury :)
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DLUGOSC_MENU 1
#define ILOSC_MIEJSC 12
#define ILOSC_RZEDOW 3
struct danePasazera
{
	char imie[40];
	char naziwsko[40];
	bool potwierdzenie;
};
time_t rawTime;
struct samolot
{
	int nrRejsu;
	struct danePasazera miejsca[12]; //name, surname, confirmation
	struct tm *timeinfo;
};
struct samolot *tabelaRejsow;
int ileRejsow = 0;
void pokazMiesca(struct samolot *samolot)
{
	printf("\n\n\n");
	for(int a = 0; a < ILOSC_MIEJSC; a++)
	{
		if(strlen(samolot->miejsca[a].imie) == 0 ) //free
		{
			printf("[%d]", a+1);
		}
		else if(samolot->miejsca[a].potwierdzenie == true)
		{
			printf("[V]");
		}
		else
		{
			printf("[X]");
		}
		if(!((a+1)%(ILOSC_MIEJSC/ILOSC_RZEDOW)))
		{
			printf("\n");
		}
//		printf("%s \n", samolot->miejsca[a].imie);
	}
	printf("\n\n\n");
}
void pokazRezerwacje(struct samolot *samolot)
{
	char timeBuffer[80];
	bool ifAnyOne = false;
	for(int a =0; a< ILOSC_MIEJSC; a++)
	{
		if(strlen(samolot->miejsca[a].imie) != 0 )
		{
			ifAnyOne = true;
			strftime(timeBuffer,80,"%x - %I:%M%p",samolot->timeinfo);
			printf("Rezerwacja nr. %d : %s %s %s %d \n",a+1,samolot->miejsca[a].imie, samolot->miejsca[a].naziwsko, timeBuffer, samolot->miejsca[a].potwierdzenie);
		}
	}
	if(ifAnyOne != true)
	{
		printf("Brak rezerwacji! na lot nr %d \n", samolot->nrRejsu);
	}
}

bool sprawdzCzyWolne(struct samolot *samolot, int numer)
{
	if(numer > ILOSC_MIEJSC)
	{
		printf("Wybrane miejsce z poza zakresu! ");
		return false;
	}
	if(strlen(samolot->miejsca[numer-1].imie) == 0 ) return true;
	else
	{
		return false;
	}
}
int zarezerwujMiejsce(struct samolot *samolot, int numer, char *imie, char *nazwisko)
{
	strncpy(samolot->miejsca[numer-1].imie,imie,strlen(imie));
	strncpy(samolot->miejsca[numer-1].naziwsko,nazwisko, strlen(nazwisko));
	time (&rawTime);
	samolot->timeinfo = localtime(&rawTime);
	return 1;
}
void potwierdzRezerwacje(struct samolot *samolot)
{
	int numerMiejsca = 0;
	while(numerMiejsca <= 0 || numerMiejsca > 12)
	{
		printf("Podaj numer rezerwacji do potwierdzenia: \n");
		scanf(" %d", &numerMiejsca);
		scanf("%*c"); //to avoid non digit character in buffer!
		if(numerMiejsca <= 0 || numerMiejsca > 12)
		{
			printf("B³êdny numer. Spróbuj ponownie \n");
		}
	}
	if(!(sprawdzCzyWolne(samolot,numerMiejsca)))
	{
		samolot->miejsca[numerMiejsca-1].potwierdzenie = 1;
		printf("Miejsce %d potwierdzone! \n", numerMiejsca);
	}
	else
	{
		printf("Problem z potwierdzeniem miejsca %d\n",numerMiejsca);
	}
}
int usunRezerwacje(struct samolot *samolot, int numer)
{
	strncpy(samolot->miejsca[numer-1].imie,"", sizeof(40));
	strncpy(samolot->miejsca[numer-1].naziwsko,"", sizeof(40));
	return 1;
}
int usuwanie(struct samolot *samolot)
{
	int numerRezerwacji = 0;
	while(numerRezerwacji <= 0 || numerRezerwacji > 12)
	{
		printf("Podaj rezerwacjê do usuniêcia: \n");
		scanf(" %d", &numerRezerwacji);
		scanf("%*c"); //to avoid non digit character in buffer!
		if(numerRezerwacji <= 0 || numerRezerwacji > 12)
		{
			printf("B³êdny numer. Spróbuj ponownie \n");
		}
	}
	if(!(sprawdzCzyWolne(&samolot[0], numerRezerwacji)))
	{
		int ret = usunRezerwacje(samolot,numerRezerwacji);
		if(ret != 1 ){
			printf("Problem z usuwaniem rezerwacji nr. %d", numerRezerwacji);
		}
		else
		{
			return 1;
		}
	}
	else
	{
		printf("Nie ma nic do usuniêcia! \n");
		return 0;
	}
	return 1;
}

int rezerwacja(struct samolot *samolot)
{
	int numerMiejsca = 0;
	while(numerMiejsca <= 0 || numerMiejsca > 12)
	{
		printf("Podaj miejsce do zarezerwowania: \n");
		scanf(" %d", &numerMiejsca);
		scanf("%*c"); //to avoid non digit character in buffer!
		if(numerMiejsca <= 0 || numerMiejsca > 12)
		{
			printf("B³êdny numer. Spróbuj ponownie \n");
		}
	}

	if(sprawdzCzyWolne(&samolot[0], numerMiejsca))
	{
		char imie[40];
		char nazwisko[40];
		printf("Podaj imiê: ");
		scanf("%s", imie);
		printf("Podaj nazwisko: ");
		scanf("%s", nazwisko);
		int ret = zarezerwujMiejsce(samolot,numerMiejsca,imie,nazwisko);
		if(ret!=1)
		{
			printf("B³êdny numer. Spróbuj ponownie \n");
		}
		return 2;
	}
	else
	{
		printf("Miejsce zajête! Wybierz inne miejsce! \n");
		return 0;
	}
	return 1;
}
struct samolot * znajdzSamolot(struct samolot *tablica,int numer) //return pointer to array position
{
	struct samolot *znalezionySamolot = NULL;
	for(int a = 0; a < ileRejsow; a++)
	{
		if(tablica[a].nrRejsu == numer)
		{
			znalezionySamolot = &tablica[a];
		}
	}
	if(znalezionySamolot != NULL) return znalezionySamolot;
	else
			{
				printf("Nie ma rejsu o numerze %d! \n", numer);
				return NULL;
			}

}
char menuLotu(int numerLotu)
{
	char znak = 0;
	struct samolot *znalezionySamolot = znajdzSamolot(tabelaRejsow,numerLotu);
	if(znalezionySamolot == NULL)
	{
		return 'g'; // koniec
	}
	printf("Menu lotu %d! \nWybierz opcjê wpisuj¹c jej oznaczenie literowe: \n a) Poka¿ miejsca \n b) Poka¿ rezerwacje \n c) Zarezerwuj miejsce \n d) Usuñ rezerwacjê \n f) PotwierdŸ rezerwacjê \n g) Koniec \n", numerLotu);
	scanf(" %c", &znak); // space in " " to avoid newline symbol
	switch (znak) {
		case 'a':
			pokazMiesca(znalezionySamolot);
			break;
		case 'b':
			pokazRezerwacje(znalezionySamolot);
			break;
		case 'c':
			while(rezerwacja(znalezionySamolot) == 0);
			break;
		case 'd':
			while(usuwanie(znalezionySamolot) == 0);
			break;
		case 'f':
			potwierdzRezerwacje(znalezionySamolot);
			break;
		case 'g':
			printf("Cofnij \n");
			break;
		default:
			printf("B³êdny wybór \n");
			break;
	}
	return znak;
}
struct samolot* dodajRejsNr(struct samolot *tablica,int numerRejsu) //todo
{
	struct samolot *tablicaRet = NULL;
	tablicaRet = realloc(tablica, (ileRejsow+1)*sizeof(*tablica));
	ileRejsow++;
	tablicaRet[ileRejsow-1].nrRejsu = numerRejsu;
	printf("TablicaRejsow nr %d ma numer lotu %d \n", ileRejsow-1,tablicaRet[ileRejsow-1].nrRejsu );
	return tablicaRet;
}
struct samolot *dodajRejs(struct samolot *tab)
{
	int numerRejsu = 0;
	struct samolot *tabRet = NULL;
	printf("Dodaj numer rejsu! \n");
	scanf(" %d",&numerRejsu);
	tabRet = dodajRejsNr(tab,numerRejsu);
	return tabRet;
}
struct samolot *usunRejs(struct samolot *tab)
{
	struct samolot *tabRet = malloc(ileRejsow*sizeof(tab[0]));
	struct samolot *Pointer = NULL;
	struct samolot *pointer2 = NULL;
	int rozmiarTablicy = sizeof(tab[0]);
	int numerRejsu = 0;
	printf("Podaj numer rejsu do usuniêcia! \n");
	scanf(" %d",&numerRejsu);
	Pointer = znajdzSamolot(tab,numerRejsu);
	int byteToCopy = (Pointer-tab)*rozmiarTablicy;
//	printf("Firstpointer: %d, TabPointer: %d Roznica: %d Tablica: %d Do skopiowania %d \n",Pointer,tab,Pointer-tab,rozmiarTablicy,byteToCopy);
	memcpy(tabRet,tab,byteToCopy); //copy first part of memory
	pointer2 = &tab[ileRejsow-1]; //pointer to last element
	printf("Miejsce docelowe: %d \n", tabRet+1);
	memcpy(tabRet+(Pointer-tab),tab+(Pointer-tab+1),(pointer2-Pointer)*rozmiarTablicy); //copy rest of memset
	free(tab);
	ileRejsow--; //decrease
	return tabRet;
}
void pokazDostepneRejsy(struct samolot *tab)
{
	printf("Dostêpne rejsy: \n");
	for(int a = 0; a<ileRejsow; a++)
	{
		if(tab[a].nrRejsu)
		{
			printf("Rejs nr %d \n",tab[a].nrRejsu);
		}
	}
}
char menuLinii()
{
	char znak = 0;
	printf("Wybierz opcjê wpisuj¹c jej oznaczenie literowe: \n a) Poka¿ dostêpne rejsy \n b) Dodaj rejs \n c) Usuñ rejs \n d) Wybierz lot \n f) Koniec \n");
	scanf(" %c", &znak); // space in " " to avoid newline symbol
	switch(znak)
	{
		case 'a':
			pokazDostepneRejsy(tabelaRejsow);
			break;
		case 'b':
			tabelaRejsow = dodajRejs(tabelaRejsow);
			break;
		case 'c':
			tabelaRejsow = usunRejs(tabelaRejsow);
			break;
		case 'd':
			break;
		case 'f':
			break;
		default:
			printf("B³êdny wybór \n");
			break;

	}
	return znak;
}

int main()
{
	tabelaRejsow = (struct samolot*) malloc (sizeof(*tabelaRejsow)); //podstawowa wersja tablicy
	ileRejsow++;
	tabelaRejsow[0].nrRejsu = 1;
	char result = '0';
	char result2 = '0';
	while((result = menuLinii()) != 'f')
	{
		if(result == 'd')
		{
			int numerLotu = 0;
			printf("Podaj numer lotu, ktÃ³ry chcesz edytowac! \n");
			scanf(" %d",&numerLotu);
			while((result2 = menuLotu(numerLotu)) != 'g')
			{

			}
		}
	}

	free(tabelaRejsow);
	return 0;
}
