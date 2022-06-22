from back.UserManager import UserManager
import tkinter as tk


class Login(tk.Frame):
    login = None
    password = None
    log_in = None
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
        self.login = tk.Entry(self, width=40)
        self.login.pack(pady=20)
        self.login.insert(0, "Enter login")

        self.password = tk.Entry(self, width=40)
        self.password.pack(pady=20)
        self.password.insert(0, "Enter password")

        self.log_in = tk.Button(self, width=40, height=5)
        self.log_in["text"] = "Log in"
        self.log_in["command"] = self.go_to_login
        self.log_in["font"] = 20
        self.log_in.pack(pady=20)

        self.turn_back = tk.Button(self, width=40, height=5)
        self.turn_back["text"] = "Turn back"
        self.turn_back["command"] = self.go_to_desktop
        self.turn_back["font"] = 20
        self.turn_back.pack(pady=20)

    def go_to_desktop(self):
        self.use_window('desktop')

    def go_to_login(self):
        login = self.login.get()
        password = self.password.get()
        if self.user_manager.sign_in(login, password):
            self.use_window('main', loggin_correct=True)
        else:
            label = tk.Label(self, text="Incorrect login or password!")
            label.pack()

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)