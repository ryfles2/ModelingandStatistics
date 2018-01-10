#include <iostream>
#include <time.h>

using namespace std;

double boxMuler(double mi, double sigma);
int etap(int liczbaPrzedmiotow, int nrSemestru, double poziomTrudnosci, double * tabTrudnoœcZaliczeniaPrzedmiotu);
long losowaniePrzedzial(long min, long max);
double losowanie01();

int main()
{
	srand(time(NULL));
	int zdalo = 0;
	int nieZdalo = 0;
	int lPrzedmiotowSemestr[] = { 15,10,14,12,10,8,7 };
	double poziomTrudnosci = 0.5;
	int lDni = 0;
	double * tabTrudnoœcZaliczeniaPrzedmiotu = NULL;
	int max = 0;
	int min = 10000;
	int zdane = 0;
	for (int i = 0; i < 2000; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int pom = etap(lPrzedmiotowSemestr[j], j + 1, poziomTrudnosci, tabTrudnoœcZaliczeniaPrzedmiotu);
			if (pom == -1)
			{
				lDni = 0;
				break;
			}
			else
			{
				lDni += pom;	
			}
		}
		if (max < lDni)max = lDni;
		if (min > lDni && lDni != 0)min = lDni;
		if (lDni != 0) zdane++;
		cout << lDni << endl;
		lDni = 0;
	}
	//cout << "zdane " << zdane << endl;
	//cout << "max " << max << endl;
	//cout << "min " << min << endl;
	return 0;
}
//losowanie z przedzia³u 
long losowaniePrzedzial(long min, long max)
{
	long d = max - min + 1;
	return rand() % d + min;
}
double losowanie01()
{
	return (double)rand() / RAND_MAX;
}
//odchylenie standardowe mi-srednia sigma-odchylenie standardowe
double boxMuler(double mi, double sigma)
{
	double y1 = losowanie01();
	double y2 = losowanie01();

	double r = sqrt(-2 * log(y1));
	double theta = 2 * 3.14159265359*y2;

	double z = r*cos(theta);

	return z*sigma + mi;
}
void losTab(double tab[], int size, double prog)
{
	for (auto i = 0; i < size; i++)
	{
		while (tab[i] < prog)
		{
			tab[i] = losowanie01();
		}
		
	}

}
int etap(int liczbaPrzedmiotow, int nrSemestru, double poziomTrudnosci, double * tabTrudnoœcZaliczeniaPrzedmiotu)
{
	int dniDodatkowe = 0;
	const int dni = 152;
	if (!tabTrudnoœcZaliczeniaPrzedmiotu)
	{
		tabTrudnoœcZaliczeniaPrzedmiotu = new double[liczbaPrzedmiotow];
		for (auto i = 0; i < liczbaPrzedmiotow; i++)
		{
			tabTrudnoœcZaliczeniaPrzedmiotu[i] = 0;
		}
	}
	
	bool flag = true;
	int pom = -1;

	//inicjowanie tablicy
	if (tabTrudnoœcZaliczeniaPrzedmiotu[0] == 0)
	losTab(tabTrudnoœcZaliczeniaPrzedmiotu, liczbaPrzedmiotow, poziomTrudnosci);

	//kana³ na 4 semestrze losujemy wybran¹ specjalizacjê
	if (nrSemestru == 4)
	{
		double wybor = losowanie01();
		if (wybor <= 0.3)
		{
			poziomTrudnosci -= boxMuler(0.1, 0.05);
			
		}
		else if (wybor < 0.6)
		{
			poziomTrudnosci -= boxMuler(0.3, 0.05);
		}
		else
		{
			poziomTrudnosci += boxMuler(0.1, 0.05);
		}
	}

	//obliczanie czy zdamy semestr w maxymalnie sesji poprawkowej
	for (auto j = 0; j < 3; j++)
	{
		if (!flag)
		{
			dniDodatkowe += losowaniePrzedzial(5, 10);
			flag = true;
		}

		for (auto i = 0; i < liczbaPrzedmiotow; i++)
		{
			if (losowanie01() <= tabTrudnoœcZaliczeniaPrzedmiotu[i])
			{
				tabTrudnoœcZaliczeniaPrzedmiotu[i] = 1;

			}
			else
			{
				tabTrudnoœcZaliczeniaPrzedmiotu[i] += boxMuler(0.01, 0.05);
				flag = false;
			}
		}
	}
	int niezaliczone = 0;
	for (auto i = 0; i < liczbaPrzedmiotow; i++)
	{
		if (tabTrudnoœcZaliczeniaPrzedmiotu[i] != 1) niezaliczone++;
	}

	//wyrzucenie ze studiów
	if (niezaliczone > 4)
	{
		delete[] tabTrudnoœcZaliczeniaPrzedmiotu;
		tabTrudnoœcZaliczeniaPrzedmiotu = NULL;
		return -1;
	}
	//powtarzanie roku
	else if (niezaliczone > 2)
	{
		flag = true;
		if (nrSemestru == 1)
		{
			while (pom != -1)
			{
				pom = etap(liczbaPrzedmiotow, 1, poziomTrudnosci, tabTrudnoœcZaliczeniaPrzedmiotu);
				cout << pom << endl;
			}
			dniDodatkowe += pom;
		}
		else
		{
			while (pom != -1)
			{
				pom = etap(liczbaPrzedmiotow, nrSemestru - 1, poziomTrudnosci, tabTrudnoœcZaliczeniaPrzedmiotu);
				cout << pom << endl;
			}
			dniDodatkowe += pom;
		}
	}
	//sesja poprawkowa
	else if (niezaliczone > 0)
	{
		for (auto i = 0; i < liczbaPrzedmiotow; i++)
		{
			if (losowanie01() <= tabTrudnoœcZaliczeniaPrzedmiotu[i])
			{
				tabTrudnoœcZaliczeniaPrzedmiotu[i] = 1;
				dniDodatkowe += losowaniePrzedzial(5, 10);
			}
		}
	}

	niezaliczone = 0;
	for (auto i = 0; i < liczbaPrzedmiotow; i++)
	{
		if (tabTrudnoœcZaliczeniaPrzedmiotu[i] != 1) niezaliczone++;
	}

	if (niezaliczone == 0)
	{
		delete[] tabTrudnoœcZaliczeniaPrzedmiotu;
		tabTrudnoœcZaliczeniaPrzedmiotu = NULL;
		return dni + dniDodatkowe;
	}
	delete[] tabTrudnoœcZaliczeniaPrzedmiotu;
	tabTrudnoœcZaliczeniaPrzedmiotu = NULL;
	return -1;
}