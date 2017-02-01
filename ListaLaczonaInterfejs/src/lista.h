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
//Projekt listy ³¹czonej do katalogowania czêœci
//element: nr seryjny, opis, stan magazynowy => weze³ => Lista

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
//dzia³anie : inicjalizacja listy
//warunek pocz¹tkowy : wlista wskaznik na obiekt typu Lista
//warunek koñcowy: inicjalizacja pustej listy
void inicjujListe(Lista * wlista);
//dzia³anie : sprawdzenie czy lista jest pusta
//warunek pocz¹tkowy : wlista jako wskaznik na obiekt typu Lista
//warunek koñcowy: true jesli lista jest pusta, false jeœli nie
bool czyPustaLista(const Lista *wlista);
//dzia³anie : sprawdzenie czy lista jest pe³na
//warunek pocz¹tkowy : wlista jako wskaznik na zaincjalizowan¹ liste
//warunek koñcowy: true jesli pe³na, false jeœli niepe³na
bool czyPelnaLista(const Lista *wlista);
//dzia³anie : zwraca ilosc pozycji w liscie
//warunek pocz¹tkowy :  wlista jako wskaznik na zaincjalizowan¹ liste
//warunek koñcowy: liczba pozycji
unsigned int podajLiczbePozycji(const Lista *wlista);
//dzia³anie : dodaje pozycje na koniec listy
//warunek pocz¹tkowy :  wlista jako wskaznik na zaincjalizowan¹ liste
//warunek koñcowy: true jesli dodano, false jesli nie dodano
bool dodajPozycje(Element element, Lista *wlista);
//dzia³anie : usuwa ostatni element z listy
//warunek pocz¹tkowy : wskaznik do Listy
//warunek koñcowy: true jesli usuniete
bool usunPozycje(Lista *wlista);
//dzia³anie : uruchamia wFunc na wszystkich elementach z listy
//warunek pocz¹tkowy : wskaznik do listy wlista, wskaznik do funkcji wFunc
//warunek koñcowy: brak
void przejdz( Lista *wlista, void (*wFunc)(Element element));
//dzia³anie : zeruje cala liste
//warunek pocz¹tkowy : wskaznik do listy wlista
//warunek koñcowy: brak
void czyscListe(Lista *wlista);
#endif /* SRC_LISTA_H_ */
