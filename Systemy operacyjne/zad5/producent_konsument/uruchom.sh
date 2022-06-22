#!/bin/bash

while getopts :p:P:k:K:r:R:m:M:t:T:n:N: OPCJA
do
    case $OPCJA in
        t|T) declare -ri LICZBA_TOWAROW=$OPTARG;;
        m|M) readonly NAZWA_MAGAZYNU=$OPTARG;;
        n|N) readonly NAZWA_POLKI=$OPTARG;;
        r|R) declare -ri ROZMIAR_MAGAZYNU=$OPTARG;;
        k|K) declare -ri CZAS_KONSUMPCJI=$OPTARG;;
        p|P) declare -ri CZAS_PRODUKCJI=$OPTARG;;
        *) echo Nieznana opcja $OPTARG; exit 2;;
    esac
done

if test ${LICZBA_TOWAROW:-0} -le 0; then
    readonly LICZBA_TOWAROW=100 
fi
if test ${ROZMIAR_MAGAZYNU:-0} -le 0; then
    readonly ROZMIAR_MAGAZYNU=3 
fi
readonly PREFIX_MAGAZYNU="${NAZWA_MAGAZYNU:-mag_fifo_$(date +%T)}"
readonly PREFIX_POLKI=${NAZWA_POLKI:-polka}

shift $(($OPTIND-1))
readonly BLOKADA_MAGAZYNU=${1:-${PREFIX_MAGAZYNU}_lock}
readonly PELNY_SYNC=${2:-sock_full}
readonly PUSTY_SYNC=${3:-stream_empty}
readonly PELNY_FLAGA=${4:-file_full}

if ! test -d $PREFIX_MAGAZYNU; then
    mkdir $PREFIX_MAGAZYNU
else
    rm -f $PREFIX_MAGAZYNU/$PREFIX_POLKI* 2>/dev/null
fi

if ! test -f $BLOKADA_MAGAZYNU; then
    touch $BLOKADA_MAGAZYNU
fi

rm $PELNY_SYNC $PUSTY_SYNC $PELNY_FLAGA 2>/dev/null

echo "fpg-${0}: liczba towarów $LICZBA_TOWAROW, prefiks magazynu $PREFIX_MAGAZYNU, rozmiar magazynu $ROZMIAR_MAGAZYNU, \
    czas konsumpcji ${CZAS_KONSUMPCJI:-losowy}, czas produkcji ${CZAS_PRODUKCJI-losowy}."

bash producent_konsument/konsument.sh $PUSTY_SYNC $PELNY_SYNC $PELNY_FLAGA $BLOKADA_MAGAZYNU $PREFIX_MAGAZYNU $PREFIX_POLKI $LICZBA_TOWAROW $ROZMIAR_MAGAZYNU $CZAS_KONSUMPCJI&
bash producent_konsument/producent.sh $PELNY_SYNC $PUSTY_SYNC $PELNY_FLAGA $BLOKADA_MAGAZYNU $PREFIX_MAGAZYNU $PREFIX_POLKI $LICZBA_TOWAROW $ROZMIAR_MAGAZYNU $CZAS_PRODUKCJI&

wait %1

rm -f $BLOKADA_MAGAZYNU
rmdir $PREFIX_MAGAZYNU