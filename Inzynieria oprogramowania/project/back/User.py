class User:
    def __init__(self, nickname, password, account, wonGames, lostGames):
        self.nickname = nickname
        self.password = password
        self.account = account
        self.wonGames = wonGames
        self.lostGames = lostGames

    def get_info(self):
        return self.nickname, self.password, self.account, self.wonGames, self.lostGames

    def change_account(self, new_account):
        self.account += new_account

    def add_won_game(self):
        self.wonGames += 1

    def add_lost_game(self):
        self.lostGames += 1
