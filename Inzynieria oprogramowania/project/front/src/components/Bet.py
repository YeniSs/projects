import tkinter as tk


class Bet(tk.Frame):
    bet = None
    accept = None
    turn_back = None
    user_balance = None

    def __init__(self, master=None, use_window=None, user_balance=lambda x: True):
        super().__init__(master)
        self.master = master
        self.use_window = use_window
        self.user_balance = user_balance

    def create_vue(self):

        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.bet = tk.Entry(self, width=40)
        self.bet.pack(pady=20)
        self.bet.insert(0, "Enter value")

        self.accept = tk.Button(self, width=40, height=5)
        self.accept["text"] = "Accept"
        self.accept["command"] = self.go_to_accept
        self.accept["font"] = 20
        self.accept.pack(pady=20)

        self.turn_back = tk.Button(self, width=40, height=5)
        self.turn_back["text"] = "Turn back"
        self.turn_back["command"] = self.go_to_turn_back
        self.turn_back["font"] = 20
        self.turn_back.pack(pady=20)

    def go_to_turn_back(self):
        self.use_window('main')

    def go_to_accept(self):
        bet = self.bet.get()
        self.use_window('play', bet_state=int(bet))

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
