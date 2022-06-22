def metoda_siecznych(funkc, poczatek, koniec, iteracje, warunek, epsilon):
    print('\n\n*** OBLICZANIE MIEJSCA ZEROWEGO METODA SIECZNYCH ***')
    poprzedni = 0
    ostatnia_iteracja = 0
    for i in range (iteracje):
        ostatnia_iteracja = i
        if funkc(poczatek) == funkc(koniec):
            print('!!!! METODA SIECZNYCH: Dzielenie przez zero !!!!\n')
            break
        wynik = poczatek - (koniec-poczatek)*funkc(poczatek)/(funkc(koniec) - funkc(poczatek))
        #print('Iteracja: %d, x = %0.7f, f(x    ) = %0.7f, poprzedni wynik = %0.7f' % (i+1, wynik, funkc(wynik),poprzedni))
        poczatek = koniec
        koniec = wynik
        if warunek == 1 and iteracje > 0 :
            if abs(wynik - poprzedni) < epsilon:
                break
        else:
            if abs(funkc(wynik)) < epsilon:
                break
        if i != iteracje-1:
            poprzedni = wynik
    print('*** SUKCES ***')
    return wynik, poprzedni, abs(wynik-poprzedni), ostatnia_iteracja