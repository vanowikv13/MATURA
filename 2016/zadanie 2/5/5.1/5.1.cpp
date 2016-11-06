// 5.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Student {
	string imie, nazwisko, pesel;
	int ilewys;
	vector<string>listbook;
};

struct wypo {
	string pesel, ksiazka;
};

fstream plik; //plik do pobierania danych

string copyx(int x, int y, string a) {
	string newa="";
	for (int i = x; i < y; i++)
		newa += a[i];
	return newa;
}

void wypisz(Student * obiekt) {
	cout << obiekt->pesel << " " << obiekt->imie << " " << obiekt->nazwisko << endl;
}

int main()
{
	vector<Student> stud; //zawsze zaczynaj od jeden
	plik.open("studenci.txt",ios::in);
	string napis;

	//pobieranie danych z pliku
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
		 ad.ilewys = 0;
		 stud.push_back(ad);
		 

	}
	plik.close();
	plik.open("wypozyczenia.txt", ios::in);

	vector<wypo> wyp;//zawsze zaczynaj od jeden
	while (getline(plik, napis)) {

		wypo reno;
		bool hel = false;
		int pocz = 0, kon = napis.size(), i = 1;
		for (int i = 0; i < kon; i++) {
			if (napis[i] == '\t' && hel) {
				reno.pesel = copyx(pocz, i, napis);
				pocz = i + 1;
			}
			else if (napis[i] == '\t' && !hel) {
				pocz = i+1;
				hel = true;
			}

		}
		reno.ksiazka = copyx(pocz, kon, napis);
		pocz = 0; hel = false;

		wyp.push_back(reno);
		

	}

	//szukanie wystopien
	int bestintsize = 0; vector<Student>::iterator adad;
	for (vector<Student>::iterator it = stud.begin()+1; it < stud.end();it++) {
		for (auto itw = wyp.begin() + 1; itw < wyp.end(); itw++) { //kontrukcja auto jest naprawde wygodna
			if (it->pesel == itw->pesel) {
				it->ilewys++;
				it->listbook.push_back(itw->ksiazka);
			}
		}
		if (bestintsize < it->ilewys) {
			bestintsize = it->ilewys;
			adad = it;
		}
	}

	//wypisywanie
	cout << adad->imie << " " << adad->nazwisko << "liczba ksiazek : " << endl;
	for (int i = 0; i < adad->ilewys; i++)
		cout << "- " << adad->listbook[i] << endl;



	plik.close();
	system("pause");
    return 0;
}

