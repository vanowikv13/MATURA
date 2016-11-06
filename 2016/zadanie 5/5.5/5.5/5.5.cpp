// 5.5.cpp : Defines the entry point for the console application.
//wiekszosc zeczy w tym kodzie jest niepotrzebna to tylko moja inicjatywa zrobienia tego programu w takim stylu

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Student {
	string imie, nazwisko, pesel;
	vector<string>listbook;
};

struct Pokoj {
	vector<Student> stud;
	int ileks;
	int nr;
	int ilestud;
	vector<string> ksiazki;
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



int main()
{
	vector<Student> stud; //zawsze zaczynaj od jeden
	plik.open("studenci.txt", ios::in);
	string napis;
	
	///pobieranie danych z pliku dla studenta
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

	plik.close(); //zamykanie pliku
	plik.open("wypozyczenia.txt", ios::in); //otwieranie pliku

	vector<wypo> wyp;//zawsze zaczynaj od jeden //lista wypozyczonych ksiazek
	///kopiowanie ksiazek  do studenta
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
				pocz = i + 1;
				hel = true;
			}
		} //for

		//kopiowanie danych z ksiazek do studenta
		reno.ksiazka = copyx(pocz, kon, napis);
		pocz = 0; hel = false;
		wyp.push_back(reno);
	} //while
		
	///dodawanie ksiazek do studentów
	for (auto it = stud.begin() + 1; it < stud.end(); it++) {
		for (auto itw = wyp.begin() + 1; itw < wyp.end(); itw++) { //kontrukcja auto jest naprawde wygodna
			if (it->pesel == itw->pesel) {
				it->listbook.push_back(itw->ksiazka);
				break;
			}
		}
	}

	///inicjalizacja pokoji i tworzenie obiktu
	vector<Pokoj> pokoje; //obiekt pokoj
	for (int k = 0; k < 100;k++) {
		Pokoj p; p.ileks = 0;	p.nr = k; p.ilestud = 0;
		pokoje.push_back(p);
	}

	//dzialanie na plikach
	plik.close();//zamkniecie pliku
	plik.open("meldunek.txt", ios::in); //otwarcie pliku
	getline(plik, napis);//pobranie niepotrzebniego napisu

	///dodanie studenta do pokoju
	while (getline(plik, napis)) {
		string pesel = copyx(0, 11, napis);
		int nr_poko = stoi(copyx(12, napis.size(), napis));
		for (auto p = stud.begin(); p != stud.end(); p++) {
			if (pesel == p->pesel) {
				pokoje[nr_poko].stud.push_back(*p); //kopiujemy studenta do pokoju
				pokoje[nr_poko].ileks += (p->listbook.size()); //inicjalizacja zmienej w celeu zliczenia ilosci ksiazek lacznej dla studentow
				pokoje[nr_poko].ilestud++; //lista studentow
				//dodawanie student->ksiazek do p->ksiazki
				for (auto ksi = p->listbook.begin(); ksi != p->listbook.end(); ksi++) {
					pokoje[nr_poko].ksiazki.push_back(*ksi);//dodawanie ksiazek do listy
				}
				break;//przerwanie petli
			}
		}
	}
	int ileostks = 0;
	for (auto pok = pokoje.begin(); pok != pokoje.end(); pok++) {
		for (auto ksi = pok->ksiazki.begin(); ksi != pok->ksiazki.end(); ksi++) {
			for (auto ksi2 = pok->ksiazki.begin() + 1; ksi2 != pok->ksiazki.end(); ksi2++) {
				if ((&(*ksi2) != &(*ksi)) && (*ksi!="" || *ksi2!="")) {
					if (*ksi == *ksi2) {
						*ksi = "";
						pok->ileks--;
					}
				}
			}
		}
		ileostks += pok->ileks;
	}
	///liczba ksiazek gdyby zasada z pytania obowiazywala
	cout << ileostks << endl;
	plik.close();
	system("pause");
    return 0;
}

