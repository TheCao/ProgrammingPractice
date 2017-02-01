/*
 * drzewo.c
 *
 *  Created on: 28.01.2017
 *      Author: Cao
 */

#include "drzewo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
static bool naLewo(const Pozycja *p1, const Pozycja *p2)
{
	int porownanie;
	if((porownanie = strcmp(p1->imie, p2->imie)) < 0) return true;
	else if (porownanie == 0 && strcmp(p1->gatunek, p2->gatunek) < 0) return true;
	else return false;
}
static bool naPrawo(const Pozycja *p1, const Pozycja *p2)
{
	int porownanie;
	if((porownanie = strcmp(p1->imie, p2->imie)) > 0) return true;
	else if(porownanie == 0 && strcmp(p1->gatunek, p2->gatunek) > 0) return true;
	else return false;
}
static void dodajWezel(Wezel * nowy, Wezel * wroot)
{
	if(naLewo(&nowy->pozycja,&wroot->pozycja))
	{
		if(wroot->lewy == NULL) wroot->lewy = nowy;
		else dodajWezel(nowy, wroot->lewy); // jesli nie dodajemy na lewo to szukamy czy po lewej stronie nie mo¿na dodac pozycji
	}
	else if (naPrawo(&nowy->pozycja, &wroot->pozycja))
	{
		if(wroot->prawy == NULL) wroot->prawy = nowy;
		else dodajWezel(nowy, wroot->prawy);
	}
	else // identyczna pozycja
	{
		printf("Blad funkcji dodajWezel!");
		exit(1);
	}
}
typedef struct para
{
	Wezel * rodzic;
	Wezel * dziecko;
} Para;
static Para szukajPozycji(const Pozycja *wp, const Drzewo *wDrzewo)
{
	Para szukana;
	szukana.rodzic = NULL;
	szukana.dziecko = wDrzewo->root; // zaczynam przeszukianie w dó³ od korzenia drzewa
	if(szukana.dziecko == NULL)
	{
		return szukana;
	}
	while(szukana.dziecko !=NULL)
	{
		// sprawdzam czy szukana pozycja jest na lewo lub na prawej stronie aktualnej pozycji
		if(naLewo(wp, &(szukana.dziecko->pozycja)))
		{
			szukana.rodzic = szukana.dziecko;
			szukana.dziecko = szukana.dziecko->lewy; // znaleziona pozycja po lewo
		}
		else if (naPrawo(wp,&(szukana.dziecko->pozycja)))
		{
			szukana.rodzic = szukana.dziecko;
			szukana.dziecko = szukana.dziecko->prawy;
		}
		else // pozycje s¹ identyczne czyli szukana.dziecko jest adresem aktualnego wêz³a
			break;
	}
	return szukana;
}



static Wezel * utworzWezel(const Pozycja *wp)
{
	Wezel * nowy;
	nowy = (Wezel *) malloc(sizeof(Wezel));
	if(nowy != NULL)
	{
		nowy->lewy = NULL;
		nowy->prawy = NULL;
		nowy->pozycja = *wp;
	}
	return nowy;
}
void inicjujDrzewo(Drzewo *wDrzewo)
{
	wDrzewo->root = NULL;
	wDrzewo->rozmiar = 0;
}
bool czyDrzewoPuste(const Drzewo *wDrzewo)
{
	if(wDrzewo->root == NULL)
	{
		return true;
	}
	else return false;
}
bool czyDrzewoPelne(const Drzewo *wDrzewo)
{
	if(wDrzewo->rozmiar >= MAXPOZYCJI) return true;
	else return false;
}
int ilePozycji(const Drzewo *wDrzewo)
{
	return wDrzewo->rozmiar;
}
bool dodajPozycje(const Pozycja *wp, Drzewo *wDrzewo)
{
	//sprawdzic czy jest miejsce, czy pozycji nie ma w drzewie
	if(czyDrzewoPelne(wDrzewo))
	{
		printf("Drzewo pe³ne");
		return false;
	}
	if(szukajPozycji(wp, wDrzewo).dziecko != NULL)
	{
		printf("Próba dodania istniej¹cej pozycji! \n");
		return false;
	}
	Wezel * nowy;
	nowy = utworzWezel(wp);
	if(nowy == NULL)
	{
		printf("Nie mo¿na utworzyc wêz³a!");
		return false;
	}
	wDrzewo->rozmiar++;
	if(wDrzewo->root == NULL) wDrzewo->root = nowy; // przypadek kiedy drzewo jest puste
	else dodajWezel(nowy,wDrzewo->root);
	return true;
}
static void usunWezel(Wezel ** pwezel) //adres wskaŸnika do typu Wezel *
{
	Wezel * tymczas;
	if((*pwezel)->lewy == NULL)
	{
		tymczas = *pwezel;
		*pwezel = (*pwezel)->prawy;
		free(tymczas);
	}
	else if ((*pwezel)->prawy == NULL )
	{
		tymczas = *pwezel;
		*pwezel = (*pwezel)->prawy;
		free(tymczas);
	}
	else // usuwany weze³ ma 2 dzieci
	{
		// szukanie miejsca aby dolaczyc prawe poddrzewo
		for(tymczas = (*pwezel)->lewy; tymczas->prawy !=NULL; tymczas=tymczas->prawy)
		{
			continue;
		}
		tymczas->prawy = (*pwezel)->prawy;
		tymczas=*pwezel;
		*pwezel = (*pwezel)->lewy;
		free(tymczas);
	}
}
bool usunPozycje(const Pozycja *wp, Drzewo *wDrzewo)
{
	Para szukana;
	szukana = szukajPozycji(wp,wDrzewo);
	if(szukana.rodzic == NULL)
	{
		printf("Brak danej pozycji w drzewie. Nic nie zosta³o usuniête!");
		return false;
	}
	if(szukana.rodzic == NULL)
	{
		// usuwanie pozycje w korzeniu
		usunWezel(&wDrzewo->root);
	}
	else if(szukana.rodzic->lewy == szukana.dziecko)
	{
		usunWezel(&szukana.rodzic->lewy);
	}
	else
	{
		usunWezel(&szukana.rodzic->prawy);
	}
	wDrzewo->rozmiar--;
	return true;


}
bool czyWDrzewie(const Pozycja *wp, const Drzewo *wDrzewo)
{
	return (szukajPozycji(wp,wDrzewo).dziecko == NULL) ? false:true;
}
static void poKolei(const Wezel * korzen, void (*wFunc)(Pozycja pozycja))
{
	if(korzen != NULL)
	{
		poKolei(korzen->lewy, wFunc);
		(*wFunc)(korzen->pozycja);
		poKolei(korzen->prawy,wFunc);
	}
}
void przejdz(const Drzewo *wDrzewo, void (*wFunc)(Pozycja pozycja))
{
	if(wDrzewo != NULL) poKolei(wDrzewo->root, wFunc);
}
static void usunWszyskieWezly(Wezel *wsk)
{
	Wezel *wprawy;
	if(wsk != NULL)
	{
		wprawy = wsk->prawy;
		usunWszyskieWezly(wsk->lewy);
		free(wsk);
		usunWszyskieWezly(wprawy);
	}
}
void usunWszystko(Drzewo *wDrzewo)
{
	if(wDrzewo != NULL)
	{
		usunWszyskieWezly(wDrzewo->root);
	}
	wDrzewo->root = NULL;
	wDrzewo->rozmiar = 0;
}
