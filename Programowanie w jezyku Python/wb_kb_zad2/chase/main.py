import random
import math
import json
import csv
import argparse
import os
import logging
import configparser
import copy


# zmienne globalne
random.seed()
liczba_tur = 50
liczba_owiec = 15
init_pos_limit = 10.0
sheep_move_dist = 0.5
wolf_move_dist = 1.0
move = [[0, sheep_move_dist], [0, -sheep_move_dist], [sheep_move_dist, 0], [-sheep_move_dist, 0]]

wolf_position = [0.0, 0.0]
sheep_position = [[0.0, 0.0]] * liczba_owiec
csv_array = [[0, 0]] * liczba_tur
dictionaries = []


# poczatkowa pozycja owcy
def sheep_start_position():
    for i in range(liczba_owiec):
        sheep_position[i] = [random.uniform(-init_pos_limit, init_pos_limit),random.uniform(-init_pos_limit, init_pos_limit)]
        logging.info("sheep_start_position() - new sheep position: [" + str(sheep_position[i]) + "]")
    logging.debug("sheep_start_position() called, returned: " + sheep_position.__str__())
    return sheep_position


# losowanie kierunku ruchu owcy
def sheep_move_direction():
    direction = random.choice(move)
    logging.debug("sheep_move_direction() called, returned: " + direction.__str__())
    return direction


# wybor najblizszej owcy
def choose_sheep():
    closest_sheep_distance = float("inf")
    for i in range(liczba_owiec):
        if sheep_position[i] != [None, None]:
            current_sheep_distance = math.sqrt(
                (wolf_position[0] - sheep_position[i][0]) ** 2 + (wolf_position[1] - sheep_position[i][1]) ** 2)
            if current_sheep_distance < closest_sheep_distance:
                closest_sheep_distance = current_sheep_distance
                closest_sheep_index = i
    logging.debug(
        "choose_sheep() called, returned: " + str(closest_sheep_index) + " and " + str(closest_sheep_distance))
    return closest_sheep_index, closest_sheep_distance


# ruchy owiec
def sheep_move():
    for i in range(liczba_owiec):
        if sheep_position[i] != [None, None]:
            move = sheep_move_direction()
            sheep_position[i][0] += move[0]
            sheep_position[i][1] += move[1]
            logging.info("sheep_move() - sheep number: " +
                         str(i + 1) +
                         " moved to position: [" +
                         str(sheep_position[i][0]) +
                         ", " + str(sheep_position[i][1]) + "]")
    logging.debug("sheep_move() called, nothing returned")


# decyzja wilka
def wolf_move(sheep_alive):
    sheep_target_index, closest_sheep = choose_sheep()
    if closest_sheep <= wolf_move_dist:
        # owca w zasiegu ruchu - decyzja o zjedzeniu
        print("Wolf ate sheep with index ", sheep_target_index + 1, "\n")
        wolf_position[0] = sheep_position[sheep_target_index][0]
        wolf_position[1] = sheep_position[sheep_target_index][1]
        sheep_position[sheep_target_index] = [None, None]
        sheep_alive -= 1
        logging.info("wolf_move() - wolf eats sheep number: " + str(sheep_target_index) +
                     " and moved to position: [" + str(wolf_position[0]) +
                     ", " + str(wolf_position[1]) + "]")
    else:
        # brak owcy w zasiegu ruchu - ruch w strone najblizszej owcy
        print("Wolf is chasing sheep with index ", sheep_target_index + 1, "\n")
        move_axis_x = ((sheep_position[sheep_target_index][0] - wolf_position[0]) / closest_sheep) * wolf_move_dist
        move_axis_y = ((sheep_position[sheep_target_index][1] - wolf_position[1]) / closest_sheep) * wolf_move_dist
        wolf_position[0] += move_axis_x
        wolf_position[1] += move_axis_y
        logging.info("wolf_move() - wolf target sheep number:" + str(sheep_target_index + 1) +
                     " and moved to position: [" + str(wolf_position[0]) +
                     ", " + str(wolf_position[1]) + "]")
    logging.debug("wolf_move(" + str(sheep_alive) + ") called, returned: " + str(sheep_alive))
    return sheep_alive


# informacje o rundzie
def round_info(round_id, sheep_alive):
    print("Round number:", round_id + 1)
    print("Wolf position [x,y]: {:.3f}, {:.3f}".format(wolf_position[0], wolf_position[1]))
    print("Number of alive sheep:", sheep_alive)
    logging.debug("round_info(" + str(round_id) + ", " + str(sheep_alive) + ") called, nothing returned")


# zapis pozycji kazdego zwierzecia podczas kazdej tury do pliku .json
def export_to_json(dir):
    if dir:
        directory = os.getcwd()
        path = directory + '\\' + dir
        if not os.path.exists(path):
            os.mkdir(dir)
        os.chdir(dir)
    with open("pos.json", "w") as json_file:
        json.dump(dictionaries, json_file, indent=4)
        json_file.write("\n")
    logging.debug("export_to_json(" + str(dir) + ") called, nothing returned")


# zapis liczby zywych owiec podczas kazdej tury do pliku .csv
def export_to_csv():
    with open("alive.csv", "w", newline='', encoding='utf-8') as csv_file:
        writer = csv.writer(csv_file, delimiter=';')
        for row in csv_array:
            writer.writerow((row[0], row[1]))
    logging.debug("export_to_csv() called, nothing returned")


# sprawdzenie czy liczba jest calkowita i dodatnia
def check_number(value):
    x = int(value)
    if x <= 0:
        logging.error("check positive(" + value + ") called, value must be positive")
        raise argparse.ArgumentTypeError('%s value must be positive' % value)
    return x


# wczytanie dodatkowego pliku konfiguracyjnego
def main_config(file):
    config = configparser.ConfigParser()
    config.read(file)
    init = config.get('Terrain', 'InitPosLimit')
    sheep = config.get('Movement', 'SheepMoveDist')
    wolf = config.get('Movement', 'WolfMoveDist')
    if float(init) < 0 or float(sheep) < 0 or float(wolf) < 0:
        logging.error('Not positive number passed as argument')
        raise ValueError('Not positive number')
    logging.debug("main_config(", file, ") called, returned: " + str(init) + str(sheep) + str(wolf))
    return float(init), float(sheep), float(wolf)


def main():
    global liczba_owiec, liczba_tur, init_pos_limit, sheep_move_dist, wolf_move_dist, csv_array, sheep_position
    wait = False
    directory = False
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--config', help='set config file', action='store', dest='conf_file', metavar='FILE')
    parser.add_argument('-d', '--dir', help='where to save files', action='store', dest='directory', metavar='DIR')
    parser.add_argument('-l', '--log', help='create log file with log LEVEL', action='store', dest='log_lvl',
                        metavar='LEVEL')
    parser.add_argument('-r', '--rounds', help='number of rounds', action='store', dest='round_number',
                        type=check_number,
                        metavar='NUM')
    parser.add_argument('-s', '--sheep', help='number of sheep', action='store', dest='sheep_no', type=check_number,
                        metavar='NUM')
    parser.add_argument('-w', '--wait', help='wait for input after round', action='store_true')
    args = parser.parse_args()

    if args.conf_file:
        init_pos_limit, sheep_move_dist, wolf_move_dist = main_config(args.conf_file)
    if args.directory:
        directory = args.directory
    if args.log_lvl:
        if args.log_lvl == 'DEBUG':
            lvl = logging.DEBUG
        elif args.log_lvl == 'INFO':
            lvl = logging.INFO
        elif args.log_lvl == 'WARNING':
            lvl = logging.WARNING
        elif args.log_lvl == 'ERROR':
            lvl = logging.ERROR
        elif args.log_lvl == 'CRITICAL':
            lvl = logging.CRITICAL
        else:
            raise ValueError('Invalid log level!')
        with open('chase.log', 'w'):
            pass
        logging.basicConfig(level=lvl, filename='chase.log')
    if args.round_number:
        liczba_tur = args.round_number
        csv_array = [[0 for x in range(2)] for y in range(liczba_tur)]
    if args.sheep_no:
        liczba_owiec = args.sheep_no
        sheep_position = [[0.0 for x in range(2)] for y in range(liczba_owiec)]
    if args.wait:
        wait = args.wait
    simulation(liczba_owiec, liczba_tur, wait, directory)


def simulation(liczba_owiec, liczba_tur, wait, directory):
    sheep_position = sheep_start_position()
    sheep_alive = liczba_owiec

    for turn_number in range(liczba_tur):
        dictionary = {
            'round_number': turn_number + 1,
            'wolf_position': wolf_position,
            'sheep_position': sheep_position
        }
        dictionaries.append(copy.deepcopy(dictionary))
        csv_array[turn_number] = [turn_number + 1, sheep_alive]

        round_info(turn_number, sheep_alive)
        sheep_move()
        sheep_alive = wolf_move(sheep_alive)
        if sheep_alive == 0:
            print("All the sheep were eaten.")
            break
        if liczba_tur == turn_number + 1:
            print("End of rounds.")
        if wait:
            input("Press ENTER to continue...")
    export_to_json(directory)
    export_to_csv()


if __name__ == '__main__':
    main()
