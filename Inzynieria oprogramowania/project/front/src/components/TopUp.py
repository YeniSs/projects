from back.UserManager import UserManager
import tkinter as tk


class TopUp(tk.Frame):
    ammount = None
    accept = None
    turn_back = None
    user_manager: UserManager

    def __init__(self, user_manager: UserManager, master=None, use_window=None):
        super().__init__(master)
        self.user_manager = user_manager
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.ammount = tk.Entry(self, width=40)
        self.ammount.pack(pady=20)
        self.ammount.insert(0, "Enter ammount to top up")

        self.accept = tk.Button(self, width=40, height=5)
        self.accept["text"] = "Accept"
        self.accept["command"] = self.go_to_accept
        self.accept["font"] = 20
        self.accept.pack(pady=20)

        self.turn_back = tk.Button(self, width=40, height=5)
        self.turn_back["text"] = "Turn back"
        self.turn_back["command"] = self.go_to_main
        self.turn_back["font"] = 20
        self.turn_back.pack(pady=20)

    def go_to_main(self):
        self.use_window('main')

    def go_to_accept(self):
        self.user_manager.add_money_to_account(int(self.ammount.get()))
        self.use_window('main')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)