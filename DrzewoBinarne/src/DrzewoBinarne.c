/*
 ============================================================================
 Name        : DrzewoBinarne.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"
#include <ctype.h>

#define MAXROZ 20

char menu(void);
void dodajzw(Drzewo * wd);
void usunzw(Drzewo *wd);
void pokazzw(const Drzewo *wd);
void szukajzw(const Drzewo *wd);
void wyswpoz(Pozycja pozycja);
void duzelit(char *lan);
char *wczytaj(char *z, int ile);

int main(void) {
	Drzewo zwierz;
	char wybor;
	inicjujDrzewo(&zwierz);
	while((wybor = menu()) !='q')
	{
		switch(wybor)
		{
			case'd': dodajzw(&zwierz);
			break;
			case 'w': pokazzw(&zwierz);
			break;
			case 's': szukajzw(&zwierz);
			break;
			case 'l': printf("%d zwierzat w klubie. \n", ilePozycji(&zwierz));
			break;
			case 'u': usunzw(&zwierz);
			break;
			default: printf("Bl¹d w instrukcji switch");
		}
	}
	usunWszystko(&zwierz);
	printf("Do widzenia.");
	return EXIT_SUCCESS;
}

char menu(void)
{
	int ch;
	printf("Podaj literê \n d - dodaj zwierze w - wyswietl liste zwierz¹t \n l - liczba zwierzat s - szukaj zwierzêcia \n u - usuñ zwierzê q - koniec \n");
	while((ch = getchar()) != EOF)
	{
		while(getchar()!= '\n')
		{ // odrzucenie znaku nowego wiersza
			continue;
		}
		ch = tolower(ch);
		if(strchr("dwlsuq", ch) == NULL) printf("Wybierz opcjê z menu!");
		else break;
	}
	if (ch == EOF) ch = 'q';
	return ch;
}

void dodajzw(Drzewo *wd)
{
	Pozycja tymczas;
	if(czyDrzewoPelne(wd)) printf("Brak wolnego miejsca!");
	else
	{
		puts("Podaj imie:");
		wczytaj(tymczas.imie,MAXROZ);
		puts("Podaj gatunek:");
		wczytaj(tymczas.gatunek, MAXROZ);
		duzelit(tymczas.imie);
		duzelit(tymczas.gatunek);
		dodajPozycje(&tymczas,wd);
	}
}
void pokazzw(const Drzewo *wd)
{
	if(czyDrzewoPuste(wd)) puts("Brak pozycji");
	else przejdz(wd,wyswpoz);
}
void wyswpoz(Pozycja pozycja)
{
	printf("Zwierze: %-19s Gatunek: %-19s \n", pozycja.imie, pozycja.gatunek);
}
void szukajzw(const Drzewo *wd)
{
	Pozycja tymcz;
	if(czyDrzewoPuste(wd))
	{
		puts("Brak pozycji!");
		return;
	}
	puts("Podaj imiê do znalezienia:");
	wczytaj(tymcz.imie,MAXROZ);
	puts("Podaj gatunek:");
	wczytaj(tymcz.gatunek, MAXROZ);
	duzelit(tymcz.imie);
	duzelit(tymcz.gatunek);
	printf("%s , %s ", tymcz.imie, tymcz.gatunek);
	if(czyWDrzewie(&tymcz, wd)) printf("jest cz³onkiem klubu \n");
	else printf("nie jest cz³onkiem klubu \n");
}

void usunzw(Drzewo *wd)
{
	Pozycja tymcz;
	if(czyDrzewoPuste(wd))
	{
		puts("Brak pozycji!");
		return;
	}
	puts("Podaj imiê do usuniecia:");
	wczytaj(tymcz.imie,MAXROZ);
	puts("Podaj gatunek:");
	wczytaj(tymcz.gatunek, MAXROZ);
	duzelit(tymcz.imie);
	duzelit(tymcz.gatunek);
	printf("%s , %s ", tymcz.imie, tymcz.gatunek);
	if(usunPozycje(&tymcz,wd)) printf("zosta³(a) usuniêty/a z klubu. \n");
	else printf("nie jest cz³onkiem klubu! \n");
}

void duzelit(char *lan)
{
	while(*lan != '\0')
	{
		*lan = toupper(*lan);
		lan++;
	}
}

char *wczytaj(char *z, int ile)
{
	char * wynik;
	char *tutaj;

	wynik = fgets(z,ile,stdin);
	if(wynik)
	{
		tutaj = strchr(z, '\n'); // szukanie nowego wiersza
		if(tutaj) *tutaj = '\0';
		else while(getchar() != '\n') continue;
	}
	return wynik;
}
