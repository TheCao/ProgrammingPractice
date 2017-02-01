/*
 * drzewo.h
 *
 *  Created on: 28.01.2017
 *      Author: Cao
 */

#ifndef DRZEWO_H_
#define DRZEWO_H_

#include <stdbool.h>
#define MAXPOZYCJI 10
typedef struct pozycja
{
	char imie[20];
	char gatunek[20];
} Pozycja;

typedef struct wezel
{
	Pozycja pozycja;
	struct wezel * lewy; // wskaüniki do lewej i prawej ga≥Ízi drzewa
	struct wezel * prawy;
} Wezel;

typedef struct drzewo
{
	Wezel * root;
	int rozmiar; // ca≥kowity rozmiar drzewa
} Drzewo;

void inicjujDrzewo(Drzewo *wDrzewo);
bool czyDrzewoPuste(const Drzewo *wDrzewo);
bool czyDrzewoPelne(const Drzewo *wDrzewo);
int ilePozycji(const Drzewo *wDrzewo);
bool dodajPozycje(const Pozycja *wp, Drzewo *wDrzewo);
bool usunPozycje(const Pozycja *wp, Drzewo *wDrzewo);
bool czyWDrzewie(const Pozycja *wp, const Drzewo *wDrzewo);
void przejdz(const Drzewo *wDrzewo, void (*wFunc)(Pozycja pozycja));
void usunWszystko(Drzewo *wDrzewo);


#endif /* DRZEWO_H_ */
