#include "header.h"
using namespace std;
double suma1(int i, double **macierz, double wektorX[])
{
    if((i-1)>=0) 
    {
        double suma1=0;
        for(int j=0; j<=i-1; j++) 
        {
            suma1=suma1+(macierz[i][j]*wektorX[j]);
        }
        return suma1;
    }
    else 
    {
        return 0;
    };
}

double suma2(int i, int n, double **macierz, double buforX[])
{
    double suma2=0;
    for(int j=i+1; j<=n; j++) 
    {
        suma2=suma2+(macierz[i][j]*buforX[j]);
    }
    return suma2;
}

void przekatniowo_dominujaca(int n, double **macierz, double wektor[])
{
    double sprawdzenie[n];
    double bufor[n];
    double bufor2;

    double suma_pozostalych=0;

    for (int i=0; i<n; i++)         // szukamy elementu dominujacego wierszy.
    {
        int kolumna = 0;
        double maks = macierz[i][0];
        for (int j=1; j<n; j++) 
        {
            if(fabs(maks)<fabs(macierz[i][j]))
            {
                maks = macierz[i][j];
                kolumna = j;
            }
        }
        if (i!=kolumna) 
        {
        for (int k=0; k<n; k++)         // zamiana elementu dominujacego na przekatna.
        {
            bufor[k] = macierz[i][k];
            macierz[i][k] = macierz[kolumna][k];
            macierz[kolumna][k] = bufor[k];
        }
        bufor2 = wektor[i];
        wektor[i] = wektor[kolumna];
        wektor[kolumna] = bufor2;
        }
    }

    for (int i=0; i<n; i++) 
    {
    double maks = macierz[i][0];
    int kolumna = 0;
        for (int j=1; j<n; j++) 
        {
            if(fabs(maks)<fabs(macierz[i][j])) 
            {
                maks = macierz[i][j];
                kolumna = j;
            }
        }
    sprawdzenie[i] = kolumna;       // zawiera indeksy maksymalnych wartosci z kazdego wiersza.
    }

    // SORTOWANIE INDEKSOW ELEMENTOW MAKSYMALNYCH.
    int temp;
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-1; j++)
        {
            if (sprawdzenie[j]>sprawdzenie[j+1])
            {
                temp = sprawdzenie[j];
                sprawdzenie[j] = sprawdzenie[j+1];
                sprawdzenie[j+1] = temp;
            }
        }
    }
    for (int i=0; i<n; i++)
    {
        if (sprawdzenie[i]!=i)      // sprawdzenie czy jest przekotniowo dominujaca.
         {
            cout << endl << "Macierz nie jest przekatniowo dominujaca, obliczenia moga byc bledne" << endl;
            return;
        }
    }
    for (int i=0; i<n; i++)     // sprawdzenie czy jest przekatniowo dominujaca z innymi elementami wiersza.
    {
        for (int j=0; j<n; j++) 
        {
            if (j!=i)
            {
                suma_pozostalych = suma_pozostalych+fabs(macierz[i][j]);
            }
        }
        if (fabs(macierz[i][i])<=suma_pozostalych)
        {
            cout << "Macierz nie jest przekatniowo dominujaca, obliczenia moga byc bledne" << endl;
            return;
        }
    suma_pozostalych=0;
    }



    cout << endl << "Macierz jest przekatniowo dominujaca" << endl;
    cout << endl << "Zaladowana macierz A po przeksztalceniach:" << endl;
    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++) 
        {
            cout << setw(8) << macierz[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Wektor b po przeksztalceniach:" << endl;
    for (int i=0; i<n; i++) 
    {
        cout << setw(8) << wektor[i];
        cout << endl;
    }
}

double wyznacznik(int n, double **macierz)
{
    double **test = new double*[n];
    for(int i=0; i<n; i++)	test[i] = new double[n];        // tworzy nxn macierz.

    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++) test[i][j] = macierz[i][j];     // do testu przypisuje wartosci z main.
    }
    double tmp = 1.0;
    for (int k=0; k<n-1; k++) 
    {
        for (int i=k+1; i<n; i++)
            for (int j=n-1; j>=k; j--)
                test[i][j] = test[i][j] - test[i][k]*test[k][j]/test[k][k];
    }
    for (int i=0; i<n; i++)
        tmp = tmp * test[i][i];
    stringstream tmp2;
    tmp2 << setprecision(10) << fixed << tmp;
    double det = stod(tmp2.str());
    return det;

}