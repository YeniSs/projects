import tkinter as tk


class CoinUse(tk.Frame):
    heads = None
    tails = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_windows = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.heads = tk.Button(self, width=40, height=5)
        self.heads["text"] = "Heads"
        self.heads["command"] = self.go_to_heads
        self.heads["font"] = 20
        self.heads.pack(pady=20)

        self.tails = tk.Button(self, width=40, height=5)
        self.tails["text"] = "Tails"
        self.tails["command"] = self.go_to_tails
        self.tails["font"] = 20
        self.tails.pack(pady=20)

    def go_to_heads(self):
        self.use_windows('coin_flip', use_mode='heads')

    def go_to_tails(self):
        self.use_windows('coin_flip', use_mode='tails')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
