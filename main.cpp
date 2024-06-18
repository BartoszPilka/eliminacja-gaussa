#include <iostream>
#include <math.h>

using namespace std;
const double EPSILON = 1e-7;

void wczytaj(double** macierz, int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << "Podaj elementy wiersza " << i+1 << ": " << endl;
        for(int j = 0; j < n+1; j++)
        {
            cin >> macierz[i][j];
        }
    }
}

void wczytajTest(double** macierz)
{
    int n = 4;
    double macierzTest[n][n+1] =
    {
        {2.25, -2.5, 4, -5.25, -1},
        {-3, -7.5, 6.5, 0, 17},
        {-6.25, -12.5, 0.25, 5.25, 24.25},
        {9, 10, 7, -21, -33}
    };

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n+1; j++)
        {
            macierz[i][j] = macierzTest[i][j];
        }
    }
}

void wyswietl(double** macierz, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n+1; j++)
        {
            cout << macierz[i][j] << "\t";
        }
        cout << endl;
    }
}

bool czySymetryczna(double** macierz, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(macierz[i][j] != macierz[n-i][n-j])
                return false;
        }
    }
    return true;
}

void zamienkolumny(double** macierz, double* wyniki, int n, int kol1, int kol2)
{
    for(int i = 0; i < n; i++)
    {
        swap(macierz[i][kol1], macierz[i][kol2]);
        swap(wyniki[kol1], wyniki[kol2]);
    }
}

void eliminacjaGaussa(double** macierz, double* wyniki, int n, int wybor)
{
    double m, s;
    for (int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            //sprawdzenie czy dzielnik jest rowny zero i obsluga jezeli prawda (zamiana wierszy)
            if(wybor == 2)
            {
                int maxWiersz = i;
                double maxWartosc = abs(macierz[i][i]);

                for(int k = i+1; k < n; k++)
                {
                    if(abs(macierz[k][i] > maxWartosc))
                    {
                        maxWiersz = k;
                        maxWartosc = abs(macierz[k][i]);
                    }
                }
                //zamiana wierszy
                if(maxWartosc > EPSILON)
                    swap(macierz[i], macierz[maxWiersz]);
            }
            m = -macierz[j][i] / macierz[i][i];
            for(int k = i+1; k <= n; k++)
                macierz[j][k] += m * macierz[i][k];
            macierz[j][i] = 0;
        }
    }

    //wypelnianie zerami wartosci mniejszych od 1e-7
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n+1; j++)
        {
            if(abs(macierz[i][j]) < EPSILON)
                macierz[i][j] = 0;
        }
    }

    //wyliczanie niewaidomych
    for(int i = n-1; i >= 0; i--)
    {
        s = macierz[i][n];
        for(int j = n-1; j >= i+1; j--)
            s -= macierz[i][j] * wyniki[j];
        if(abs(macierz[i][i]) < EPSILON)
            cout << "Dzielnik zero" << endl;
        wyniki[i] = s/macierz[i][i];
    }
}

void menu()
{
    int dane, n, wybor;
    double** macierz;
    double* wyniki;

    cout << "1 - Gauss podstawowy | 2 - Gauss rozszerzony (zamiana wierszy)" << endl;
    cin >> wybor;
    cout << "1 - wczytaj wlasne dane | 2 - dane testowe" << endl;
    cin >> dane;

    switch(dane)
    {
    case 1:
        cout << "Jaki rozmiar macierzy rozszerzonej potrzebujesz? ";
        cin >> n;
        macierz = new double*[n+1];
        wyniki = new double[n];
        for(int i = 0; i < n+1; i++)
            macierz[i] = new double[n];
        wczytaj(macierz, n);
        break;
    case 2:
        n = 4;
        macierz = new double*[n+1];
        wyniki = new double[n];
        for(int i = 0; i < n+1; i++)
            macierz[i] = new double[n];
        wczytajTest(macierz);
        break;
    default:
        cout << "Nieprawidlowy numer" << endl;
        break;
    }

    cout << "Macierz przed eliminacja: " << endl;
    wyswietl(macierz, n);
    eliminacjaGaussa(macierz, wyniki, n, wybor);
    cout << endl << "Macierz po eliminacji: " << endl;
    wyswietl(macierz, n);

    cout << "Wyniki: " << endl;
    for(int i = 0; i < n; i++)
        cout << "x" << i+1 << " = " << wyniki[i] << endl;
}

int main()
{
    menu();
    return 0;
}
