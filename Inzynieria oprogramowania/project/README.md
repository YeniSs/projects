# IO_grupa01

DON'T READ ME
too late now

Test commita

Wlasciwe readme:
Nazwa serwera SQL: KASYNOIO
Tworzac nowy serwer za pomoca instalatora tworzy sie jakby nowa instancja.
W efekcie pozniej i tak to figuruje jako "laptopcostam/KASYNOIO" przynajmniej to cos z laptopem u mnie.
W SQL management studio mozna registered name, nie wiem, czy to cos daje, ja zmienilam tam na "KASYNOIO".
Przy laczeniu z baza danych zrobilam "./KASYNOIO", wiec jesli najpierw macie nazwe tego glownego serwera, to powinno dzialac.

Nazwa bazy danych: KasynoDB

Utworzona klasa user i userManager.
User jest na potrzeby UserManagera, raczej wszystko jest w niego opakowane.
Funkcje UserManagera do korzystania "na zewnatrz":

takeFromAccount(int) - funkcja odejmujaca jakas wartosc od konta przy stawianiu zakladu. Podawac dodatnia.
Automatycznie updateuje uzytkownika w bazie danych.

addAccountAndGame(int, bool) - przy konczeniu gry. Jesli uzytkownik wygral, to ma dostac okreslona kwote, jesli nie, to int
ma byc rowny 0. Odejmujemy juz w ramach zakladu na poczatku. Bool to informacja, czy wygral. Jesli tak, to true, jesli nie, False.
To zmienia licznik wygranych i przegranych gier.

checkAccount - zwraca stan konta obecnie zalogowanego uzytkownika

signIn(login, password) - przyjmuje login i haslo. Jesli nie ma takiego uzytkownika/zle haslo - zwraca false (bedzie trzeba w gui wyrzucic jakis komunikat), 
jesli dane poprawne to zwraca True i ustawia uzytkownika biezacej sesji.

signOut - nie przyjmuje nic, czysci pole obecnego uzytkownika. Po signOut powinno powrocic sie do startowego okienka z zaloguj.

getCurrentUserInfo - zwraca wszystkie dane o obecnym uzytkowniku w liscie.

addNewUser(login, haslo) - sprawdza, czy nie ma uzytkownika o takiej nazwie w bazie. Jak  jest to zwraca false, jak nie ma to dodaje nowego do bazy i zwe

addNewUserFinal(login, haslo) - obudowanie funkcji addNewUser, zwraca boola jak addNewUser oraz stringa z komunikatem

signInFinal(login, passwordToCheck) - obudowanie signIn, zwraca boola i stringa z komunikatem
        
bet(someMoney) - jesli stan konta jest wystarczajacy, odejmuje sume i zwraca true, jesli nie jest wystarczajacy, zwraca false

betFinal(someMoney) - obudowanie funkcji bet, zwraca dodatkowo stringa z informacja