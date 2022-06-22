#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <sstream>

double suma1(int i, double **macierz, double wektorX[]);
double suma2(int i, int n, double **macierz, double buforX[]);
void przekatniowo_dominujaca(int n, double **macierz, double wektor[]);
double wyznacznik(int n, double **macierz);

#endif
