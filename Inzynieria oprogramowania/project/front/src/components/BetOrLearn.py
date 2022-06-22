import tkinter as tk


class BetOrLearn(tk.Frame):
    zaklad = None
    nauka = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_windows = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.zaklad = tk.Button(self, width=40, height=5)
        self.zaklad["text"] = "Simple mode"
        self.zaklad["command"] = self.go_to_zaklad
        self.zaklad["font"] = 20
        self.zaklad.pack(pady=20)

        self.nauka = tk.Button(self, width=40, height=5)
        self.nauka["text"] = "Training mode"
        self.nauka["command"] = self.go_to_nauka
        self.nauka["font"] = 20
        self.nauka.pack(pady=20)

    def go_to_zaklad(self):
        self.use_windows('bet', mode='postaw_zaklad')

    def go_to_nauka(self):
        self.use_windows('game_or_instruction', mode='tryb_nauki')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
