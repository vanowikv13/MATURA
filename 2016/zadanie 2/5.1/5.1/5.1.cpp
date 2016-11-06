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
	vector<Student> stud;
	plik.open("studenci.txt",ios::in);
	string napis;

	//pobieranie danych z pliku
	getline(plik, napis);
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
		 stud.push_back(ad);

	}
	system("pause");
    return 0;
}

