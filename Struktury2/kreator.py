from random import randint
import random

lista = {}
imionaPlik = open('imiona.txt', 'r')
nazwiskaPlik = open('nazwiska.txt', 'r')
graczePlik = open('gracze.txt', "a")
imionaPlikLista = imionaPlik.read().splitlines()
nazwiskaPlikLista = nazwiskaPlik.read().splitlines()
random.seed()


for numer in range(1,19,1):
	randomImie = random.choice(imionaPlikLista)
	randomNazwisko = random.choice(nazwiskaPlikLista)
	lista.update({numer: randomImie + " " + randomNazwisko})

for numer in range(1,random.randint(40,100),1):
	numerRandomowy = random.randint(1,18)
	ileRzutow = random.randint(0,30)
	ileRzutowCelnych = random.randint(0,ileRzutow)
	asysty = random.randint(0,30)
	faule = random.randint(0,10)
	#string = "{0!s}".format(numerRandomowy) + " " + "{:s}".format(lista.get(numerRandomowy)) + " " + "{0!s}".format(ileRzutow) + " " + "{0!s}".format(ileRzutowCelnych)+ " " + "{0!s}".format(asysty) + " " + "{0!s}".format(faule) + "\n"
	string = '{0} {1} {2} {3} {4} {5} \n'.format(numerRandomowy, lista.get(numerRandomowy),ileRzutow, ileRzutowCelnych,asysty,faule)
	graczePlik.write(string)
	
imionaPlik.close()
nazwiskaPlik.close()
graczePlik.close()
