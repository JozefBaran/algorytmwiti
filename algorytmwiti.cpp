#include <iostream>
#include <fstream>

using namespace std;

struct task
{
	int czas; //czas trwania
	int wartosc; //ważność zadania
	int koniecCzasu; //do kiedy ma się skończyć
};

int main()
{
	task tab[100];
	ifstream wczytaj("data.txt");
	int n;
	string s;
	string s1[11] = { "data.10:", "data.11:","data.12:","data.13:","data.14:","data.15:","data.16:","data.17:","data.18:","data.19:","data.20:" };

	for (int zbior = 0; zbior < 11; zbior++) 
	{
		while (s != s1[zbior])
		{
			wczytaj >> s;
		}
		cout << "Dane " << s << endl;

		wczytaj >> n; //wczytanie ilości zadań

		for (int i = 0; i < n; i++) //wczytanie parametrów kolejnych zadań
		{
			wczytaj >> tab[i].czas >> tab[i].wartosc >> tab[i].koniecCzasu;
		}

		int N = 1 << n; //liczbę zadań w postaci binarnej
		int* Tablica = new int[N];
		Tablica[0] = 0;

		for (int kombinacje = 1; kombinacje < N; kombinacje++)
		{
			int tmp = 0;
			for (int i = 0, b = 1; i < n; i++, b *= 2)
			{
				if (kombinacje & b)
				{
					tmp += tab[i].czas;
				}
			}
			Tablica[kombinacje] = 100000;
			for (int j = 0, b = 1; j < n; j++, b *= 2)
			{
				if (kombinacje & b)
				{
					Tablica[kombinacje] = min(Tablica[kombinacje], Tablica[kombinacje - b] + tab[j].wartosc * max(tmp - tab[j].koniecCzasu, 0));
				}
			}
		}
		cout << "Optymalne rozwiązanie: " << Tablica[N - 1] << endl;
		delete[] Tablica;
	}

	wczytaj.close();
	cout << endl << "Koniec działania programu." << endl;
	cin.get();
}