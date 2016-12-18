
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char plik[20] = "gracze.txt";
struct daneZawodnika{
	int numer;
	char imie[40];
	char nazwisko[40];
	int oddaneRzuty;
	int trafienia;
	int asysty;
	int faule;
	double skutecznosc;
};

struct daneZawodnika tablicaStruktur[19];
FILE *plikTekstowy;
void policzSkutecznosc(struct daneZawodnika *tablica)
{
   for(int i = 1; i<=18;i++)
   {
        double trafienia = tablica[i].trafienia * 1.0;
        double rzuty = tablica[i].oddaneRzuty * 1.0;
        tablica[i].skutecznosc = (trafienia/rzuty);
   }
}
void wczytaj(FILE *source, struct daneZawodnika *tablica )
{
	char linijka[256] = "";
	char linijkaTemp[256];
	int przesuniecie,numer;
	int element=1;
	char *wsk, *wskSpace;
	wsk = linijka;
	char temp[20];
	while(fgets(linijka,sizeof(linijka),source))
	{
		while(strlen(linijka)) // till linijka buffer isnt empty
		{
			memset(temp,0, sizeof(temp));
			wskSpace = strchr(linijka, ' '); // looking for next space char
			if(wskSpace == 0) break; // while there is no space on linijka buffer just break while loop
			przesuniecie = wskSpace-wsk;
			strncpy(temp,linijka,przesuniecie);
			strncpy(linijkaTemp,linijka+przesuniecie+1,sizeof(linijka));
			strncpy(linijka, linijkaTemp, 100);

			switch(element){
			case(1):
                numer = atoi(temp);
                element++;
                break;
            case(2):
                //tablica[numer].imie = temp;
                strncpy(tablica[numer].imie,temp,sizeof(temp));
                element++;
                break;
            case(3):
                strncpy(tablica[numer].nazwisko,temp,sizeof(temp));
                element++;
                break;
            case(4):
                tablica[numer].oddaneRzuty += atoi(temp);
                element++;
                break;
            case(5):
                tablica[numer].trafienia += atoi(temp);
                element++;
                break;
            case(6):
                tablica[numer].asysty += atoi(temp);
                element++;
                break;
            case(7):
                tablica[numer].faule += atoi(temp);
                element++;
                break;
            default:
                printf("BÅ‚Ä…d wczytywania");
			}

		}
		element = 1;
	}

}
void wyswietlStatystyki(struct daneZawodnika *tablica)
{
    double skutecznoscZespolu = 0.0;
    for(int i =1; i<=18;i++)
    {
        printf("Zawodnik %s %s [%d]=> Rzuty: %d Faule: %d Skutecznoœc‡: %.3f \n", tablica[i].imie, tablica[i].nazwisko, i, tablica[i].oddaneRzuty, tablica[i].faule, tablica[i].skutecznosc);
        skutecznoscZespolu += tablica[i].skutecznosc;
    }
    printf("Skutecznoœc ca³ego zespo³u wynosi : %.3f \n", skutecznoscZespolu/18);
}
int main()
{
	//otwieranie pliku
	if((plikTekstowy = fopen(plik, "r")) == NULL)
	{
		printf("B³¹d otwierania pliku %s", plik);
	}

	wczytaj(plikTekstowy, tablicaStruktur);
	policzSkutecznosc(tablicaStruktur);
	wyswietlStatystyki(tablicaStruktur);
	//zamykanie pliku
	if(fclose(plikTekstowy) != 0)
	{
		printf("B³¹d zamykania pliku %s", plik);
		return 1;
	}
	return 0;
}
