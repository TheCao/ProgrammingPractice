/*
 * lista.h
 *
 *  Created on: 24.01.2017
 *      Author: Cao
 */

#ifndef SRC_LISTA_H_
#define SRC_LISTA_H_
#include <stdbool.h>
#define DLUGOSCOPISU 50
//Projekt listy ��czonej do katalogowania cz�ci
//element: nr seryjny, opis, stan magazynowy => weze� => Lista

typedef struct
{
	int numerSeryjny;
	char opis[DLUGOSCOPISU];
	int stanMagazynowy;
} Element;

typedef struct wezel
{
	Element element;
	struct wezel * nastepny;
} Wezel;

typedef Wezel * Lista;


//Prototypy funkcji interfejsu
//dzia�anie : inicjalizacja listy
//warunek pocz�tkowy : wlista wskaznik na obiekt typu Lista
//warunek ko�cowy: inicjalizacja pustej listy
void inicjujListe(Lista * wlista);
//dzia�anie : sprawdzenie czy lista jest pusta
//warunek pocz�tkowy : wlista jako wskaznik na obiekt typu Lista
//warunek ko�cowy: true jesli lista jest pusta, false je�li nie
bool czyPustaLista(const Lista *wlista);
//dzia�anie : sprawdzenie czy lista jest pe�na
//warunek pocz�tkowy : wlista jako wskaznik na zaincjalizowan� liste
//warunek ko�cowy: true jesli pe�na, false je�li niepe�na
bool czyPelnaLista(const Lista *wlista);
//dzia�anie : zwraca ilosc pozycji w liscie
//warunek pocz�tkowy :  wlista jako wskaznik na zaincjalizowan� liste
//warunek ko�cowy: liczba pozycji
unsigned int podajLiczbePozycji(const Lista *wlista);
//dzia�anie : dodaje pozycje na koniec listy
//warunek pocz�tkowy :  wlista jako wskaznik na zaincjalizowan� liste
//warunek ko�cowy: true jesli dodano, false jesli nie dodano
bool dodajPozycje(Element element, Lista *wlista);
//dzia�anie : usuwa ostatni element z listy
//warunek pocz�tkowy : wskaznik do Listy
//warunek ko�cowy: true jesli usuniete
bool usunPozycje(Lista *wlista);
//dzia�anie : uruchamia wFunc na wszystkich elementach z listy
//warunek pocz�tkowy : wskaznik do listy wlista, wskaznik do funkcji wFunc
//warunek ko�cowy: brak
void przejdz( Lista *wlista, void (*wFunc)(Element element));
//dzia�anie : zeruje cala liste
//warunek pocz�tkowy : wskaznik do listy wlista
//warunek ko�cowy: brak
void czyscListe(Lista *wlista);
#endif /* SRC_LISTA_H_ */
