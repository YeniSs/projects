import tkinter as tk


class GameUse(tk.Frame):
    coin_flip = None
    slots = None
    roulette = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.coin_flip = tk.Button(self, width=40, height=5)
        self.coin_flip["text"] = "Coin Flip"
        self.coin_flip["command"] = self.go_to_coin_flip
        self.coin_flip["font"] = 20
        self.coin_flip.pack(pady=20)

        self.slots = tk.Button(self, width=40, height=5)
        self.slots["text"] = "Slots"
        self.slots["command"] = self.go_to_slots
        self.slots["font"] = 20
        self.slots.pack(pady=20)

        self.roulette = tk.Button(self, width=40, height=5)
        self.roulette["text"] = "Roulette"
        self.roulette["command"] = self.go_to_roulette
        self.roulette["font"] = 20
        self.roulette.pack(pady=20)

    def go_to_coin_flip(self):
        self.use_window('bet_or_learn', state='coin_flip')

    def go_to_roulette(self):
        self.use_window('bet_or_learn', state='roulette')

    def go_to_slots(self):
        self.use_window('bet_or_learn', state='slots')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
