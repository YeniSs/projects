def regula_falsi(funkc, poczatek , koniec, iteracje, warunek, epsilon):
    print('\n\n*** OBLICZANIE MIEJSCA ZEROWEGO REGULA FALSI ***')
    poprzedni = 0
    ostatnia_iteracja = 0
    wymuszone_zatrzymanie = 0
    if funkc(poczatek) * funkc(koniec) >= 0:
        print('!!!! REGULA FALSI: Podano bledny zakres !!!!\n')
        wymuszone_zatrzymanie = 1
    wynik = poczatek
    for i in range (iteracje):
        if wymuszone_zatrzymanie == 1:
            break
        ostatnia_iteracja = i
        wynik = (poczatek * funkc(koniec) - koniec * funkc(poczatek))/(funkc(koniec) - funkc(poczatek))
        #print('Iteracja: %d, x = %0.7f, f(x) = %0.7f, poprzedni wynik = %0.7f' % (i+1, wynik, funkc(wynik),poprzedni))
        
        if funkc(wynik) == 0:
            break

        elif funkc(wynik) * funkc(poczatek) < 0:
            koniec = wynik
        else:
            poczatek = wynik

        if warunek == 1 and iteracje > 0 :
            if abs(wynik - poprzedni) < epsilon:
                break
        else:
            if abs(funkc(wynik)) < epsilon:
                break
        if i != iteracje-1:
            poprzedni = wynik
    if wymuszone_zatrzymanie != 1:
        print('*** SUKCES ***')
    return wynik, poprzedni, abs(wynik-poprzedni), ostatnia_iteracja