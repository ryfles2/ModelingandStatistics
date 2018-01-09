#include <iostream>
#include <time.h>

using namespace std;

double boxMuler(double mi, double sigma);
int etap(int liczbaPrzedmiotow, int nrSemestru, double poziomTrudnosci);
long losowaniePrzedzial(long min, long max);
double losowanie01();

int main()
{
	srand(time(NULL));

	int lPrzedmiotowSemestr[] = { 15,10,14,12,10,8,7 };
	double poziomTrudnosci = 0.5;
	int lDni = 0;

	for (int i = 0; i < 2000; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int pom = etap(lPrzedmiotowSemestr[j], j + 1, poziomTrudnosci);
			if (pom == -1)
			{
				cout << 0 << endl;
				lDni = 0;
				break;
			}
			else
			{
				lDni += pom;
			}
		}
		cout << lDni << endl;
		lDni = 0;
	
	}
	
	

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
int etap(int liczbaPrzedmiotow, int nrSemestru, double poziomTrudnosci)
{
	int dniDodatkowe = 0;
	const int dni = 152;
	double * tabTrudnoœcZaliczeniaPrzedmiotu = new double[liczbaPrzedmiotow];
	bool flag = true;
	int pom = -1;

	losTab(tabTrudnoœcZaliczeniaPrzedmiotu, liczbaPrzedmiotow, poziomTrudnosci);

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
				tabTrudnoœcZaliczeniaPrzedmiotu[i] += boxMuler(0.1, 0.05);
				flag = false;
			}
		}
	}
	int niezaliczone = 0;
	for (auto i = 0; i < liczbaPrzedmiotow; i++)
	{
		if (tabTrudnoœcZaliczeniaPrzedmiotu[i] != 1) niezaliczone++;
	}

	if (niezaliczone > 4)
	{
		delete[] tabTrudnoœcZaliczeniaPrzedmiotu;
		return -1;
	}
	else if (niezaliczone > 2)
	{
		if (nrSemestru == 1)
		{
			while (pom != -1)
			{
				pom = etap(liczbaPrzedmiotow, 1, poziomTrudnosci);
			}
			dniDodatkowe += pom;
		}
		else
		{
			while (pom != -1)
			{
				pom = etap(liczbaPrzedmiotow, nrSemestru - 1, poziomTrudnosci);
			}
			dniDodatkowe += pom;
		}
		
	}
	else if (niezaliczone > 0)
	{
		dniDodatkowe += losowaniePrzedzial(5, 10);

		for (auto i = 0; i < liczbaPrzedmiotow; i++)
		{
			if (losowanie01() <= tabTrudnoœcZaliczeniaPrzedmiotu[i])
			{
				tabTrudnoœcZaliczeniaPrzedmiotu[i] = 1;
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
		return dni + dniDodatkowe;
	}
	delete[] tabTrudnoœcZaliczeniaPrzedmiotu;
	return -1;
}