// 5.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

string copyx(int x, int y, string a) { //kopiuje stringa od x(z x) do y(bez y)
	string newa = "";
	for (int i = x; i < y; i++)
		newa += a[i];
	return newa;
}


int main()
{

	int liczba_os[100]; //zerowanie tablicy liczby osób w pokojach
	//w pliku najwieksza wartoscia jest 70
	for (int i = 0; i < 100; i++)
		liczba_os[i] = 0;
	
	fstream plik;
	plik.open("meldunek.txt", ios::in); //otwarcie pliku
	string napis;
	getline(plik, napis);//pobranie niepotrzebniego napisu
	int najwieksza = 0,norma=0;
	while (getline(plik, napis)) {
		liczba_os[norma = stoi(copyx(12, napis.size(), napis))]++;//zwiekszenie pokoiu
		if (norma > najwieksza)
			najwieksza = norma;
	}

	double suma=0;
	for (int i = 1; i < 71; i++)
		suma += liczba_os[i];
	double srednia = suma / najwieksza;
	std::cout << std::setprecision(5) << srednia << endl;

	
	
	plik.close(); //zamkniecie pliku
	system("pause");
	return 0;
}

