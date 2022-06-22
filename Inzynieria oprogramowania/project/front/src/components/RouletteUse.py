import tkinter as tk


class RouletteUse(tk.Frame):
    red = None
    black = None
    green = None
    title = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=30)

        self.title = tk.Label(self, text='Use color', width=40, height=5)
        self.title['background'] = '#5D5FEF'
        self.title["font"] = 32
        self.title.pack(pady=20)

        self.red = tk.Button(self, width=40, height=5)
        self.red["background"] = "#FF0000"
        self.red["command"] = self.use_red
        self.red.pack(pady=20)

        self.black = tk.Button(self, width=40, height=5)
        self.black["background"] = "#000000"
        self.black["command"] = self.use_black
        self.black.pack(pady=20)

        self.green = tk.Button(self, width=40, height=5)
        self.green["background"] = "#00FF00"
        self.green["command"] = self.use_green
        self.green.pack(pady=20)

    def use_red(self):
        self.use_window('roulette', use_mode='red')

    def use_black(self):
        self.use_window('roulette', use_mode='black')

    def use_green(self):
        self.use_window('roulette', use_mode='green')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
