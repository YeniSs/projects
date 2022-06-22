#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <sstream>
#include "header.h"

using namespace std;

int main()
{
    int N, menu = 1, b = 1, iteracje, kryterium;
    double E;
    while(menu==1)
    {
        system("cls");
        cout << "Podaj ilosc rownan: ";
        cin >> N;

        double ** macierz = new double*[N];

        for(int i=0; i<N; i++)
            macierz[i] = new double[N+1];

        double *wektor = new double[N]; // tablica z wynikami (po znaku =)
        double *wektorX = new double[N]; // tablica z niewiadomymi x
        double *buforX = new double [N]; //bufor tablicy z niewiadomymi x

        for (int i=0; i<N; i++)
            wektorX[i] = 0; // zerowanie niewiadomych x

        // SPRAWDZAMY CZY PLIK SIE ZGADZA I ZAWIERA POPRAWNA MACIERZ
        fstream plik1("j.txt");
        if(!plik1)
        {
            cout << "Blad otwarcia pliku. Nastapi zamkniecie programu\n";
            system("pause");
            return 0;
        }
        char tab[10];       // tablica zawierajaca ostatni element.
        int licznik = 0;      // zlicza ilosc elementow w macierzy.
        do
        {
            plik1 >> tab; // przekazanie do tab
            licznik++;
        } while(plik1.eof()==false);


        plik1.close();

        // JEZELI MACIERZ W PLIKU JEST POPRAWNA -> OTWIERAMY PLIK I PRZYPISUJEMY DO MACIERZY
        if(licznik/(N+1)==N)
        {
            ifstream plik("j.txt");
            if(!plik)
            {
                cout << "Blad otwarcia pliku. Nastapi zamkniecie programu." << endl;
                system("pause");
                return 0;
            }
            else {
                for(int i=0; i<N; i++)
                {
                    for(int j=0; j<N+1; j++)
                    {
                        if (j<N)
                        {
                            plik >> macierz[i][j];  // wszystkie elementy oprocz ostatniej kolumny -> A.
                        }
                        else
                        {
                            plik >> wektor[i];   // ostatnia kolumna -> b.
                        }
                    }
                }
                plik.close();
            }
            cout << endl << "Zaladowana macierz A:" << endl;
            for(int i=0; i<N; i++)
            {
                for(int j=0; j<N; j++)
                {
                    cout << setw(8) << macierz[i][j]; //wyswietlenie macierzy
                }
                cout << endl;
            }
            cout << endl << "Wektor b:" << endl;
            for (int i=0; i<N; i++)
            {
                cout << setw(8) << wektor[i];
                cout << endl;
            }
            cout << endl;
            if (wyznacznik(N, macierz)==0)
            {
                cout << "Wyznacznik macierzy jest rowny 0, macierz jest nieoznaczona albo sprzeczna" << endl;
                return 0;
            };
            cout << "Wyznacznik macierzy jest rozny od zera, macierz nie jest ani nieoznaczona, ani sprzeczna" << endl;
            przekatniowo_dominujaca(N, macierz, wektor);

            //GLOWNA ITERACJA
            cout << endl << "Podaj warunek stopu algorytmu:" << endl;
            cout << "1. Spelnienie warunku nalozonego na dokladnosc" << endl;
            cout << "2. Osiagniecie zadanej liczby iteracji" << endl;
            cout << "wybor: ";
            cin >> kryterium;
            if (kryterium==1)
            {
                cout << endl << "Podaj wartosc epsilon: ";
                cin >> E;
            }
            else
            {
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iteracje;
            }
            if(kryterium == 1)
            {
                if(N==4)
                {
                    double r1, r2, r3, r4, licznik=0;
                    do
                    {
                        licznik++;
                        double *temporaryX = new double[N];
                        for (int i=0; i<N; i++)
                        {
                            buforX[i] = wektorX[i];
                            temporaryX[i] = wektorX[i];
                        }
                        for (int i=0; i<N; i++)
                        {
                            for (int j=0; j<N; j++)
                            {
                                wektorX[i] = (1/macierz[i][i])*(wektor[i]-suma1(i, macierz, wektorX)-suma2(i, N, macierz, buforX));
                            }
                        }
                        r1 = fabs(wektorX[0]-temporaryX[0]);
                        r2 = fabs(wektorX[1]-temporaryX[1]);
                        r3 = fabs(wektorX[2]-temporaryX[2]);
                        r4 = fabs(wektorX[3]-temporaryX[3]);

                        cout<<r3<<endl;
                    } while(r1>=E && r2>=E && r3>=E && r4>=E);
                }
                if(N==3)
                {
                    double r1, r2, r3, licznik=0;
                    do
                    {
                        licznik++;
                        double *temporaryX = new double[N];
                        for (int i=0; i<N; i++)
                        {
                            buforX[i] = wektorX[i];
                            temporaryX[i] = wektorX[i];
                        }
                        for (int i=0; i<N; i++)
                        {
                            for (int j=0; j<N; j++)
                            {
                            wektorX[i] = (1/macierz[i][i])*(wektor[i]-suma1(i, macierz, wektorX)-suma2(i, N, macierz, buforX));
                            }
                        }
                    r1 = fabs(wektorX[0]-temporaryX[0]);
                    r2 = fabs(wektorX[1]-temporaryX[1]);
                    r3 = fabs(wektorX[2]-temporaryX[2]);
                    cout<<r3<<endl;
                    //<<endl<<r2<<endl<<r3<<endl;
                    } while(r1>E && r2>E && r3>E);
                }
            }
            else if(kryterium==2)
            {
                do
                {
                    for (int i=0; i<N; i++)
                    {
                        buforX[i] = wektorX[i];
                    }
                    for (int i=0; i<N; i++)
                    {
                        for (int j=0; j<N; j++)
                        {
                            wektorX[i] = (1/macierz[i][i])*(wektor[i]-suma1(i, macierz, wektorX)-suma2(i, N, macierz, buforX));
                        }
                    }
                    cout << endl << "Wyniki dla " << b << " iteracji:" << endl;
                    for (int i=0; i<N; i++)
                    {
                        cout << "x" << i+1 << " = " << wektorX[i] << endl;
                    }
                    b++;
                } while(b < iteracje+1);
            }

            cout << endl << "Wektor x:" << endl;
            for (int i=0; i<N; i++)
            {
                cout << setw(8) << wektorX[i];
                cout << endl;
            }
            b=0;
            cout << endl << "Wykonac ponownie program?" << endl;
            cout << "1. Tak" << endl;
            cout << "2. Nie" << endl;
            cout << "wybor: ";
            cin >> menu;
        }
        else {
            cout << "Podano zly rozmiar, macierz w pliku nie ma rozmiaru " << N << " x " << N << endl;
            system("PAUSE");
            system("cls");
        }
    }
    return 0;
}
