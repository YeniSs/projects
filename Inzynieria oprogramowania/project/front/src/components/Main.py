import tkinter as tk
from back.UserManager import UserManager


class Main(tk.Frame):
    use_game = None
    top_up = None
    sign_out = None
    user_manager: UserManager

    def __init__(self, user_manager: UserManager, master=None, use_window=None):
        super().__init__(master)
        self.user_manager = user_manager
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)

        self.use_game = tk.Button(self, width=40, height=5)
        self.use_game["text"] = "Use game"
        self.use_game["command"] = self.go_to_use_game
        self.use_game["font"] = 20
        self.use_game.pack(pady=20)

        self.top_up = tk.Button(self, width=40, height=5)
        self.top_up["text"] = "Top up account"
        self.top_up["command"] = self.go_to_top_up
        self.top_up["font"] = 20
        self.top_up.pack(pady=20)

        self.sign_out = tk.Button(self, width=40, height=5)
        self.sign_out["text"] = "Sign out"
        self.sign_out["command"] = self.go_to_sign_out
        self.sign_out["font"] = 20
        self.sign_out.pack(pady=10)

        label = tk.Label(self, text="Balance: " + str(self.user_manager.check_account()))
        label.pack()
        label2 = tk.Label(self, text="Won games: " + str(self.user_manager.get_won_games()))
        label2.pack()
        label3 = tk.Label(self, text="Lost games: " + str(self.user_manager.get_lost_games()))
        label3.pack()

    def go_to_use_game(self):
        self.use_window('game_use')

    def go_to_sign_out(self):
        self.user_manager.sign_out()
        self.use_window('desktop')

    def go_to_top_up(self):
        self.use_window('topup')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
