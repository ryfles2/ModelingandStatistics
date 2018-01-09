#include <iostream>
#include <time.h>

using namespace std;

double boxMuler(double mi, double sigma);
int etap1();

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 2000; i++)
	{
		int lDni = 0;
		int pom = etap1();

		if (pom == 0)
		{
			cout << 0 << endl;
		}
		else
		{
			lDni += pom;
			cout << lDni << endl;
		}
	}
	

	return 0;
}
//losowanie z przedzia³u 0 1
long losowanie01(long min, long max)
{
	long d = max - min + 1;
	return rand() % d + min;
}
//odchylenie standardowe mi-srednia sigma-odchylenie standardowe
double boxMuler(double mi, double sigma)
{
	double y1 = (double)rand() / RAND_MAX;
	double y2 = (double)rand() / RAND_MAX;

	double r = sqrt(-2 * log(y1));
	double theta = 2 * 3.14159265359*y2;

	double z = r*cos(theta);

	return z*sigma + mi;
}

int etap1()
{
	int dniDodatkowe = 0;
	int dni = 152;

	double tabTrudnoœcZaliczeniaPrzedmioty1rok[15];

	tabTrudnoœcZaliczeniaPrzedmioty1rok[0] = 0.6;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[1] = 0.8;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[2] = 0.6;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[3] = 0.8;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[4] = 0.7;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[5] = 0.9;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[6] = 0.7;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[7] = 0.9;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[8] = 0.7;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[9] = 0.6;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[10] = 0.6;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[11] = 0.8;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[12] = 0.5;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[13] = 0.9;
	tabTrudnoœcZaliczeniaPrzedmioty1rok[14] = 0.6;

	double czyZal = 0.0;
	bool flag = true;
	int pom = 0;
	int licz = 0;

	for (auto j = 0; j < 3; j++)
	{
		if (!flag)
		{
			dniDodatkowe += losowanie01(5, 10);
			flag = true;
		}

		for (auto i = 0; i < 15; i++)
		{
			czyZal = (double)rand() / RAND_MAX;
			if (czyZal <= tabTrudnoœcZaliczeniaPrzedmioty1rok[i])
			{
				tabTrudnoœcZaliczeniaPrzedmioty1rok[i] = 1;

			}
			else
			{
				tabTrudnoœcZaliczeniaPrzedmioty1rok[i] += boxMuler(0.1, 0.05);
				flag = false;
			}
		}
	}
	if (flag) return dni + dniDodatkowe;

	return 0;
}