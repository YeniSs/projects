#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

char convertToASCII(string letter)
{
    char x = letter.at(0);
    return x;
}


int main()
{
    //DEKLARACJE
        int H[8][16] =
        {
        {1,    0,    1,    0,    0,    1,    0,    1,  /**/  1,    0,    0,    0,    0,    0,    0,    0},
        {0,    1,    1,    1,    0,    1,    1,    1,  /**/  0,    1,    0,    0,    0,    0,    0,    0},
        {0,    0,    0,    1,    1,    1,    1,    0,  /**/  0,    0,    1,    0,    0,    0,    0,    0},
        {1,    0,    0,    0,    1,    1,    1,    1,  /**/  0,    0,    0,    1,    0,    0,    0,    0},
        {1,    1,    1,    0,    0,    0,    1,    0,  /**/  0,    0,    0,    0,    1,    0,    0,    0},
        {1,    1,    1,    1,    0,    0,    0,    1,  /**/  0,    0,    0,    0,    0,    1,    0,    0},
        {1,    1,    0,    1,    1,    1,    0,    1,  /**/  0,    0,    0,    0,    0,    0,    1,    0},
        {0,    1,    0,    0,    1,    0,    1,    1,  /**/  0,    0,    0,    0,    0,    0,    0,    1}
        };
    const int BYTE = 8;
    fstream wejscie;
    fstream wejscie_bin;
    fstream zakodowane;
    fstream zakodowane2;
    fstream zakodowaneASCII;
    fstream odkodowane;
    int litera_bin[BYTE];
    int kontrola[BYTE];
    int zakodowane_tab[BYTE * 2];
    int blad_tab[BYTE];
    int blad1;
    int blad2;
    int firstError;
    int secondError;
    char wybor;
    int ascii = 0;
    int q = BYTE - 1;
    char literka;

    
    int opcja;
    jeszcze_raz:
    cout << "Wybierz opcje:\n"
        << "[1] - Zakoduj wiadomosc, ktora znajduje sie w pliku txt\n"
        << "[2] - Odkoduj wiadomosc, ktora znajduje sie w pliku txt\n"
        << "[0] - Zakoncz program\n";
    cin >> opcja;
    switch (opcja) {
        case 1: //KODOWANIE WIADOMOŚĆ Z PLIKU
        {
            string linia = "";
            wejscie.open("wejscie.txt", ios::in);
            zakodowane.open("zakodowane.txt", ios::out | ios::trunc);
            zakodowane.close(); 
            zakodowane.open("zakodowane.txt", ios::out | ios::app);
            zakodowaneASCII.open("zakodowaneASCII.txt", ios::out | ios::trunc);
            zakodowaneASCII.close();
            zakodowaneASCII.open("zakodowaneASCII.txt", ios::out | ios::app);
            getline(wejscie, linia); //WCZYTANIE DO ZMIENNEJ ‘LINIA’ PIERWSZEJ A NASTEPNIE KOLEJNYCH LINII PLIKU
            for (int k = 0; k < linia.length(); k++)
            {
                int litera = int(convertToASCII(linia.substr(k, 1)));  //POBRANIE PIERWSZEJ A NASTEPNIE KOLEJNYCH LITER Z DANEJ LINII

                for (int i = BYTE - 1; i >= 0; i--)  //KONWERSJA Z ASCII NA SYSTEM BINARNY
                {
                    litera_bin[i] = litera % 2;
                    litera /= 2;
                }

                for (int i = 0; i < BYTE; i++) 
                {
                    kontrola[i] = 0; // WYPELNIENIE TABLICY KONTROLNEJ ZERAMI

                    for (int j = 0; j < BYTE; j++)
                    {
                        kontrola[i] += litera_bin[j] * H[i][j]; // LICZENIE KOLEJNYCH BITOW PARZYSTOSCI
                    }
                    kontrola[i] %= 2;
                }

                for (int i = 0; i < BYTE; i++)  // ZAPIS ODCZYTANEGO ZNAKU DO PLIKU
                {
                    zakodowane << litera_bin[i];
                }
                for (int i = 0; i < BYTE; i++)
                {   
                    zakodowane << kontrola[i];
                }
                zakodowane << endl;

                ascii = 0;
                q = BYTE - 1;
                for (int i = 0; i < BYTE*2; i++)
                {
                    ascii += litera_bin[i] * pow(2, q);
                    if (i == 7 || i == 15)
                    {
                        literka = char(ascii);
                        zakodowaneASCII << literka;
                    }
                    q--;
                }
            }
            wejscie.close();
            zakodowane.close();
            zakodowaneASCII.close();
            cout << "Zakodowano!\n\n";
            cout << "Uruchomic program jeszcze raz (Y/N)?" << endl;
            cin >> wybor;
            if (wybor == 'y' || wybor == 'Y')
            {
                system("cls");
                goto jeszcze_raz;
            }
            break;
        }

        case 2: //DEKODOWANIE WIADOMOSCI Z PLIKU
        {
            string linia = "";
            zakodowane.open("zakodowane.txt", ios::in);
            odkodowane.open("odkodowane.txt", ios::out | ios::trunc);
            odkodowane.close();
            odkodowane.open("odkodowane.txt", ios::out | ios::app);
            getline(zakodowane, linia);  //WCZYTANIE DO ZMIENNEJ ‘LINIA’ PIERWSZEJ A NASTEPNIE KOLEJNYCH LINII PLIKU
            do
            {
                blad1 = 0;
                for (int i = 0; i < linia.length(); i++)
                {
                    zakodowane_tab[i] = int(convertToASCII(linia.substr(i, 1))) - 48; //KONWERSJA Z ZAPISU BINARNEGO NA ZMIENNE INT
                }

                for (int i = 0; i < BYTE; i++)
                {
                    blad_tab[i] = 0; //ZEROWANIE TABLICY BLEDOW
                    for (int j = 0; j < BYTE * 2; j++) 
                    {
                        blad_tab[i] += zakodowane_tab[j] * H[i][j]; //MNOZENIE MACIERZY T ORAZ H JEZELI T*H!=0 OZNACZA TO ZE W ZAKODOWANEJ WIADOMOSCI ZNAJDUJE SIE BLAD
                    }
                    blad_tab[i] %= 2;
                    if (blad_tab[i] == 1) {
                        blad1 = 1; //BLAD ZOSTAL ZNALEZIONY
                    }
                }

                if (blad1 != 0)  //JEZELI BLAD2==0 TO JEST JEDEN BLAD, JEZELI BLAD2==1 TO SA 2 BLEDY
                {
                    blad2 = 0;
                    for (int i = 0; i < BYTE * 2; i++)
                    {
                        for (int j = i + 1; j < BYTE * 2; j++)  //SPRAWDZENIE ILE JEST BLEDOW - 1 CZY 2
                        {
                            blad2 = 1;
                            for (int k = 0; k < BYTE; k++)
                            {
                                if (blad_tab[k] != H[k][i] ^ H[k][j])
                                {
                                    blad2 = 0; //XOR NA WYBRANYCH KOLUMNACH MACIERZY H - SPRAWDZENIE CZY SA 2 BLEDY
                                    break;
                                }
                            }

                            if (blad2 == 1)  //PRZYPADEK DLA 2 BLEDOW
                            {
                                firstError = i;
                                secondError = j;
                                zakodowane_tab[firstError] = !zakodowane_tab[firstError]; //ZAMIANA BLEDNYCH BITOW NA POPRAWNE WARTOSCI
                                zakodowane_tab[secondError] = !zakodowane_tab[secondError]; //ZAMIANA BLEDNYCH BITOW NA POPRAWNE WARTOSCI
                                i = (BYTE * 2);
                                break;
                            }
                        }
                    }

                    if (blad1 == 1)  //PRZYPADEK DLA 1 BLEDU
                    {
                        for (int i = 0; i < (BYTE * 2); i++)
                        {
                            for (int j = 0; j < BYTE; j++)
                            {
                                if (H[j][i] != blad_tab[j])  //WYSZUKIWANIE KOLUMNY W MACIERZY H TAKIEJ SAMEJ JAK WEKTOR BŁĘDU
                                {
                                    break;
                                }
                                if (j == 7)
                                {
                                    zakodowane_tab[i] = !zakodowane_tab[i]; //PODMIANA BLEDNEGO BITU NA POPRAWNA WARTOSC
                                    i = (BYTE * 2);
                                }
                            }
                        }
                    }
                }
                ascii = 0;
                q = BYTE - 1;
                for (int i = 0; i < BYTE; i++)
                {
                    ascii += zakodowane_tab[i] * pow(2, q);
                    q--;
                }
                literka = char(ascii);
                odkodowane << literka;
                getline(zakodowane, linia);
            } while (linia != "");
            zakodowane.close();
            odkodowane.close();
            cout << "Odkodowano!\n\n";
            cout << "Uruchomic program jeszcze raz (Y/N)?" << endl;
            cin >> wybor;
            if (wybor == 'y' || wybor == 'Y')
            {
                system("cls");
                goto jeszcze_raz;
            }
            break;
        }
    
        default:
        {
            return 0;
        }
    }
    return 0;
}