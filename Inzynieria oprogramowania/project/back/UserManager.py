import pyodbc

from back.InitializeDatabase import create_database
from back.User import User


class UserManager:
    def __init__(self):
        self.currentUser = None
        self.connect_to_database_first()

    def connect_to_database_first(self):
        try:
            connection = pyodbc.connect('Driver={SQL Server};'
                                  'Server=.;'
                                  'Database=KasynoDB;'
                                  'Trusted_Connection=yes;')
        except:
            create_database()
            connection = pyodbc.connect('Driver={SQL Server};'
                                        'Server=.;'
                                        'Database=KasynoDB;'
                                        'Trusted_Connection=yes;')
        cursor = connection.cursor()
        #return cursor, connection

    def connect_to_database(self):
        connection = pyodbc.connect('Driver={SQL Server};'
                                        'Server=.;'
                                        'Database=KasynoDB;'
                                        'Trusted_Connection=yes;')
        cursor = connection.cursor()
        return cursor, connection

    def find_user(self, login):
        cursor, connection = self.connect_to_database()
        cursor.execute("SELECT * FROM Users WHERE nickname=?", (login))
        results = cursor.fetchall()
        if results == []:
            return False
        else:
            found_user = User(results[0][0], results[0][1], results[0][2], results[0][3], results[0][4])
            return found_user

    def set_current_user(self, user):
        self.currentUser = user

    def update_user_account(self):
        cursor, connection = self.connect_to_database()
        cursor.execute(("UPDATE Users SET account = ?, wonGames = ?, lostGames = ? WHERE nickname = ?"), (self.currentUser.account, self.currentUser.wonGames, self.currentUser.lostGames, self.currentUser.nickname))
        connection.commit()

    def take_from_account(self, some_money):
        self.currentUser.change_account(-some_money)
        self.update_user_account()

    def add_account_and_game(self, some_money, if_won):
        if if_won == True:
            self.currentUser.change_account(some_money)
            self.currentUser.add_won_game()
        elif if_won == False:
            self.currentUser.add_lost_game()
        self.update_user_account()

    def check_account(self):
        return self.currentUser.account

    def sign_in(self, login, password_to_check):
        user_from_database = self.find_user(login)
        if user_from_database == False:
            return False
        else:
            if user_from_database.password == password_to_check:
                self.set_current_user(user_from_database)
                return True
            else:
                return False

    def sign_out(self):
        self.currentUser = None

    def get_current_user_info(self):
        return self.currentUser.get_info()

    def add_new_user(self, new_nickname, new_password):
        cursor, connection = self.connect_to_database()
        if self.find_user(new_nickname) == False:
            cursor.execute("INSERT INTO Users (nickname, password, account, wonGames, lostGames) VALUES (?, ?, 200, 0, 0)", (new_nickname, new_password))
            connection.commit()
            return True
        else:
            return False

    def bet(self, some_money):
        if self.check_account() >= some_money:
            self.take_from_account(some_money)
            return True
        else:
            return False

    def add_money_to_account(self, some_money):
        self.currentUser.change_account(some_money)
        self.update_user_account()

    def get_won_games(self):
        return self.currentUser.wonGames

    def get_lost_games(self):
        return self.currentUser.lostGames