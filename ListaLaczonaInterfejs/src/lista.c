/*
 * lista.c
 *
 *  Created on: 24.01.2017
 *      Author: Cao
 */


#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

static void kopiujDoWezla(Element element, Wezel *wezel)
{
	wezel->element = element;
}

//Funkcje interfejsu
void inicjujListe(Lista * wlista)
{
	wlista = NULL;
}

bool czyPustaLista(const Lista *wlista)
{
	if(wlista == NULL) return true;
	else return false;
}

bool czyPelnaLista(const Lista *wlista)
{
	Wezel *wsk;
	bool ret;
	wsk = (Wezel*) malloc(sizeof(Wezel));
	if(wsk == NULL)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	free(wsk);
	return ret;
}

unsigned int podajLiczbePozycji(const Lista *wlista)
{
	int counter = 0;
	Wezel *wsk = (Wezel*)wlista;
	while(wsk->nastepny != NULL)
	{
		++counter;
		wsk = wsk->nastepny;
	}
	return counter;
}

bool dodajPozycje(Element element, Lista *wlista)
{
	Wezel *wezelTemp = (Wezel*) malloc(sizeof(Wezel));
	Wezel *szukajKonca = (Wezel*)wlista;
	if(wezelTemp == NULL)
	{
		return false; // blad alokacji miejsca na dane
	}
	kopiujDoWezla(element,wezelTemp);
	wezelTemp->nastepny=NULL; //jako ostatni element na liscie
	// dodanie polaczenia do wczesniejszego elementu listy
	if(szukajKonca == NULL) // jesli brak elementow
	{
		*wlista = wezelTemp;
	}
	else
	{
		while(szukajKonca->nastepny !=NULL)
		{
			szukajKonca = szukajKonca->nastepny;
		}
		szukajKonca->nastepny = wezelTemp;
	}
	return true;
}

bool usunPozycje(Lista *wlista)
{
	Wezel *szukajKonca = (Wezel*) wlista;
	Wezel *tempW;
	if(szukajKonca == NULL) // brak elementów
	{
		return false;
	}
	else
	{
		while(szukajKonca->nastepny!=NULL)
		{
			tempW = szukajKonca;
			szukajKonca = szukajKonca->nastepny;
		}
		tempW->nastepny = NULL; //usuniecie powi¹zania
		free(szukajKonca); //wyczyszczenie danych z pamiêci
	}
	return true;
}

void przejdz( Lista *wlista, void (*wFunc)(Element element))
{
	Wezel *wsk = (Wezel*)wlista;
	wsk=wsk->nastepny;
	while(wsk != NULL)
	{
		(*wFunc)(wsk->element);
		wsk=wsk->nastepny;
	}
}
void czyscListe(Lista *wlista)
{
	Wezel * wsk = (Wezel*)wlista;
	wsk=wsk->nastepny; //TODO: bez tego przesuniêcia przy uwalanianiu pamiêci dochodzi do kasowania jakiegoœ nadmiarowego bloku pamieci, którego nie powinno tutaj byc. Najprawdopodobniej kwestia nadmiarowego dodania pierwszego elementu do listy (element o nr 1 i pustej nazwie i ilosci 0 )
	Wezel * wskTemp = NULL;
	while(wsk != NULL)
	{
		wskTemp = wsk->nastepny;
//		printf("Wskaznik czyszczony: %p \t Wskaznik nastepny: %p \n",wsk,wskTemp);
		free(wsk);
		wsk = wskTemp;
	}
}
