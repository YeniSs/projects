import abc
import pyodbc

from back.InitializeDatabase import create_database


class Instruction:
    @abc.abstractmethod
    def view(self):
        pass

    def connect_to_database(self):
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
        return cursor, connection
