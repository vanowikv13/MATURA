// 5.3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	fstream plik;
	plik.open("studenci.txt", ios::in);
	string napis;
	int wom = 0, man = 0;
	while (getline(plik, napis)) {
		if (((napis[9] - '0') % 2) == 0)
			wom++;
		else man++;
	}

	cout << wom << " " << man << endl;
	plik.close();
	system("pause");
    return 0;
}

