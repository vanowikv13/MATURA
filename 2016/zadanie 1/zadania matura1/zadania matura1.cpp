// zadania matura1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
void zad1_2(int a)
{
	int dzielnikia=0, b=0;
	for (int i = 1; i < a; i++)
		if (a%i == 0)
			dzielnikia += i;

	dzielnikia -= 1;
	for (int i = 1; i < dzielnikia; i++)
	{
		if (dzielnikia%i == 0)
			b += i;
	}

	if (b - 1 == a)
		cout << "tak" << endl;
	else
		cout << "nie" << endl;
}

void zad2_3(int *x, int n)
{
	int klucz = x[0];
	int w = 0;
	bool a =false, b = false, c = false;
	int a1, a2, a3;
	for (int i = 0; i < n; i++)
	{
		if (x[i] < klucz)
		{
			w++;
			if (a == false || b == false || c == false)
			{
				if (!a) {
					a1 = x[i];
					a = true;
				}
				else if (!b) {
					a2 = x[i];
					b = true;
				}
				else if (!c) {
					a3 = x[3];
					c = true;
				}

				

			}
		}

		cout << "tab[1] = " << a1 << " tab[2] = " << a2 << " tab[3] = " << a3 << endl;
		cout << "w = " << w << endl;
	}
}

int main()
{

    return 0;
}

