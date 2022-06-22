#!/bin/bash
source producent_konsument/lib_producent_konsument_fifo_potoki_gniazda.sh

function konsumpcja_towaru() {
    produkcja_konsumpcja $1 'Skonsumowałem' $2
}

function pobierz_towar_z_polki() {
    rm $2 && komunikat "$1 Pobrałem towar z półki: $2"
}

readonly MY_SYNC=$1
readonly OTHER_SYNC=$2
readonly OTHER_FLAG=$3
readonly BLOKADA_MAGAZYNU=$4
readonly PREFIX_MAGAZYNU=$5
readonly PREFIX_POLKI=$6
readonly LICZBA_TOWAROW=$7
readonly ROZMIAR_MAGAZYNU=$8
readonly CZAS_KONSUMPCJI=$9 #parametr opcjonalny

exec 9>$BLOKADA_MAGAZYNU
start $LICZBA_TOWAROW $ROZMIAR_MAGAZYNU $CZAS_KONSUMPCJI

for ITERACJA in $(seq $LICZBA_TOWAROW)
do
    flock -x 9
    wyznacz_polke $ITERACJA $ROZMIAR_MAGAZYNU
    if ! test -f ${POLKA=$PREFIX_MAGAZYNU/$PREFIX_POLKI$?}; then
        komunikat "$ITERACJA Magazyn pusty, na żadnej z $ROZMIAR_MAGAZYNU półek nie ma towaru"
        mkfifo $MY_SYNC
        flock -u 9
        spotkanie_potok $ITERACJA $MY_SYNC true
        flock -x 9
    fi
    pobierz_towar_z_polki $ITERACJA $POLKA
    if [ -f $OTHER_FLAG ]; then
        spotkanie_gniazdo $ITERACJA $OTHER_SYNC && rm $OTHER_FLAG $OTHER_SYNC
    fi
    flock -u 9

    konsumpcja_towaru $ITERACJA $CZAS_KONSUMPCJI
done

stop $LICZBA_TOWAROW
