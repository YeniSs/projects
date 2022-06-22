#!/bin/bash
#!/bin/bash
source producent_konsument/lib_producent_konsument_fifo_potoki_gniazda.sh

function produkcja_towaru() {
	produkcja_konsumpcja $1 'Wyprodukowałem' $2
}
function odloz_towar_na_polke() {
	touch $2 && komunikat "$1 Odłożyłem towar na półkę: $2"
}

readonly MY_SYNC=$1
readonly OTHER_SYNC=$2
readonly MY_FLAG=$3
readonly BLOKADA_MAGAZYNU=$4
readonly PREFIX_MAGAZYNU=$5
readonly PREFIX_POLKI=$6
readonly LICZBA_TOWAROW=$7
readonly ROZMIAR_MAGAZYNU=$8
readonly CZAS_PRODUKCJI=$9 #parametr opcjonalny

exec 7>$BLOKADA_MAGAZYNU
start $LICZBA_TOWAROW $ROZMIAR_MAGAZYNU $CZAS_PRODUKCJI

for ITERACJA in $(seq $LICZBA_TOWAROW)
do
	produkcja_towaru $ITERACJA $CZAS_PRODUKCJI
	
	flock -x 7
	wyznacz_polke $ITERACJA $ROZMIAR_MAGAZYNU
	if test -f ${POLKA=$PREFIX_MAGAZYNU/$PREFIX_POLKI$?}; then
		komunikat "$ITERACJA Magazyn pełny, na wszystkich $ROZMIAR_MAGAZYNU półkach jest towar"
		touch $MY_FLAG
		flock -u 7
		spotkanie_gniazdo $ITERACJA $MY_SYNC
		flock -x 7
	fi
	odloz_towar_na_polke $ITERACJA $POLKA
	if [ -p $OTHER_SYNC ]; then
		spotkanie_potok $ITERACJA $OTHER_SYNC false
	fi
	flock -u 7
done

stop $LICZBA_TOWAROW