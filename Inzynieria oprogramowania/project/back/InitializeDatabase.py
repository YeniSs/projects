import pyodbc

def create_database():
    connection = pyodbc.connect('Driver={SQL Server};'
                                'Server=.;'
                                'Trusted_Connection=yes;')
    connection.autocommit = True
    cursor = connection.cursor()
    cursor.execute("CREATE DATABASE [kasynoDB]")
    connection.close()

    connection2 = pyodbc.connect('Driver={SQL Server};'
                                'Server=.;'
                                'Database=KasynoDB;'
                                'Trusted_Connection=yes;')
    connection2.autocommit = True
    cursor2 = connection2.cursor()
    cursor2.execute('''CREATE TABLE Users(nickname varchar(25) PRIMARY KEY, password varchar(25), account int, wonGames int, lostGames int);''')
    cursor2.execute('''CREATE TABLE Instructions(instructionName varchar(20) PRIMARY KEY, content varchar(3000));''')
    cursor2.execute("INSERT INTO Instructions VALUES ('RouletteInstruction', 'Ruletka jest popularna gra hazardowa. Kazdy kolor ma przypisane liczby. Na poczatku wybierz kolor, na jaki chcesz obstawic. Podaj kwote, jaka obstawiasz. Po wybraniu kwoty kulka krazy po ruletce. Jesli zatrzyma sie na liczbie, ktora jest przypisana do obstawionego koloru - wygrywasz.');")
    cursor2.execute("INSERT INTO Instructions VALUES ('CoinFlipInstruction', 'Rzut moneta jest najprostsza gra. Na poczatku wybierz, na jaka strone monety chcesz obstawic pieniadze. Nastepnie podaj kwote, jaka chcesz obstawic. Jesli wypadnie strona, na ktora obstawiles - wygrywasz.Jesli nie - przegrywasz.');")
    cursor2.execute("INSERT INTO Instructions VALUES ('SlotsInstruction', 'Slotsy to gra hazardowa. Polega na pociagnieciu lub nacisnieciu przycisku maszyny losujacej. 3 rolki z roznymi cyframi badz obrazkami zaczynaja sie wtedy obracac. Jesli sie zatrzymaja i na wszystkich trzech pozycjach bedzie ten sam symbol - wygrywasz. Jesli nie - przegrywasz.');")
    cursor2.execute("INSERT INTO Users VALUES ('KontoTestowe', 'HasloTestowe', 1000, 0, 0);")
    connection2.close()