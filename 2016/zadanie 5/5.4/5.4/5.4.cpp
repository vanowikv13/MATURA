// 5.4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Student {
	bool mieszka;
	string imie, nazwisko, pesel;
	
};

struct wypo {
	string pesel, ksiazka;
};

fstream plik; //plik do pobierania danych

string copyx(int x, int y, string a) {
	string newa = "";
	for (int i = x; i < y; i++)
		newa += a[i];
	return newa;
}

void wypisz(Student obiekt) {
	cout << obiekt.pesel << " " << obiekt.imie << " " << obiekt.nazwisko << endl;
}

int main()
{
	vector<Student> stud; //zawsze zaczynaj od jeden
	plik.open("studenci.txt", ios::in);
	string napis;	

	while (getline(plik, napis)) {

		Student ad;
		int ile = 0, pocz = 0, kon = napis.size(), i = 1;
		while (ile < 2) {
			if (napis[i] == '\t') {
				if (ile == 0) {
					ad.pesel = copyx(0, i, napis);
					pocz = i + 1;
				}
				if (ile == 1) {
					ad.nazwisko = copyx(pocz, i, napis);
					pocz = i + 1;
				}

				ile++;//zwiekszenie ile	
			}

			i++;
		}

		ad.imie = copyx(pocz, kon, napis);
		ad.mieszka = true;
		stud.push_back(ad);
	}

	plik.close(); //zamykanie 
	plik.open("meldunek.txt", ios::in); //otwieranie pliku
	getline(plik, napis);
	while (getline(plik, napis)) {
		string pesel = copyx(0, 11, napis); //kopiowanie pesel
		for (auto it = stud.begin(); it != stud.end(); it++) {
			if (pesel == it->pesel)
				it->mieszka = false;
		}

	}

	vector<Student> nieMieszka;
	//dodanie do osób do nie mieszka nie mieszajacych w akademiku
	for (auto it = stud.begin(); it != stud.end(); it++) {
		if (it->mieszka)
			nieMieszka.push_back(*it);
	}

	sort(nieMieszka.begin(), nieMieszka.end(), [](Student it, Student id) {return id.nazwisko > it.nazwisko; }); //sortowanie
	for (auto it = nieMieszka.begin(); it != nieMieszka.end(); it++) {
		wypisz(*it);
	}


	system("pause");
    return 0;
}

