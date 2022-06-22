from AC import Nagrywarka
from CA import Odtwarzacz
import keyboard as key

probkowanie = abs(int(input("Podaj czestotliwosc probkowania [Hz]: ")))
kwantyzacja = int(input("Wybierz poziom kwantyzacji [bit], dostepne opcje to 8, 16, 32: "))

print("Wciśnij 'r' aby nagrywac")
print("Przytrzymaj  'm' aby przestac nagrywac")
print("Wciśnij 's' aby zapisac nagranie")
print("Wciśnij 'p' aby odtworzyc nagranie")
print("Wciśnij 'z' aby odtworzyc zapisane nagranie")

REC = Nagrywarka(probkowanie=probkowanie)
PLAY = Odtwarzacz(probkowanie=probkowanie)

flag = 1
flag2 = 1
while flag == 1:
    if key.is_pressed('r'):
        while flag2 == 1:
            print('nagrywanie...')
            if key.is_pressed('m'):
                print('zakonczono nagrywanie')
                flag2 = 0
            REC.record(1)

    if key.is_pressed('p'):
        print('Odtwarzam nagranie...')
        PLAY.odtworzNagranie(REC.getAudio())

    if key.is_pressed('z'):
        print("Odtwarzam zapisane nagranie...")
        PLAY.odtworzPlik("NAGRANIE.wav")

    if key.is_pressed('s'):
        REC.zapisDoPliku('NAGRANIE', kwantyzacja)