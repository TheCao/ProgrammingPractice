/*
 * main.c
 *
 *  Created on: 24.01.2017
 *      Author: Cao
 */
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROZMIAROPISU 50
void pokazElement(Element element)
{
	printf("Element nr: %d to %s w ilosci %d \n", element.numerSeryjny, element.opis, element.stanMagazynowy);
}
char *wczytaj(char *dest, int ile)
{
	char *wynik;
	char *tutaj;
	wynik = fgets(dest,ile,stdin);
	if(wynik)
	{
		tutaj = strchr(dest, '\n'); //szukanie nowego wiersza
		if(tutaj)
		{
			*tutaj = '\0';
		}
		else
		{
			while(getchar() != '\n') continue;
		}
	}
	return wynik;
}
int main()
{
	Lista lista;
	inicjujListe(&lista);

	Element elementTymczasowy;
	if(czyPelnaLista(&lista))
	{
		fprintf(stderr, "Brak pamiêci!");
		exit(1);
	}
	// wczytywanie danych
	puts("Podaj nazwe pierwszego elementu:");
	while(wczytaj(elementTymczasowy.opis,ROZMIAROPISU) != NULL && elementTymczasowy.opis[0] != '\0')
	{
		puts("Podaj numer seryjny:");
		scanf("%d", &elementTymczasowy.numerSeryjny);
		while(getchar() != '\n') continue;
		puts("Podaj stan magazynowy: ");
		scanf("%d", &elementTymczasowy.stanMagazynowy);
		if(dodajPozycje(elementTymczasowy,&lista) == false)
		{
			fprintf(stderr, "Blad alokacji pamiêci \n");
			break;
		}
		if(czyPelnaLista(&lista))
		{
			puts("Lista jest pe³na!");
			break;
		}
		fflush(stdin);
		puts("Podaj opis nastepnego elementu (pusty wiersz konczy wpisywanie):");
	}
	// wypisywanie listy
	if(czyPustaLista(&lista))
	{
		printf("Lista jest pusta");
	}
	else
	{
		printf("Lista elementow : \n");
		przejdz(&lista,pokazElement);
	}
	printf("Wpisales %d elementow \n", podajLiczbePozycji(&lista));

	czyscListe(&lista);
//	free(&lista->nastepny);
	system("pause");
	return 0;
}
