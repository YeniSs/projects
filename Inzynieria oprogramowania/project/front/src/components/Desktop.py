import tkinter as tk


class Desktop(tk.Frame):
    login_to_account = None
    register_account = None
    quit_app = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.login_to_account = tk.Button(self, width=40, height=5)
        self.login_to_account["text"] = "Login"
        self.login_to_account["command"] = self.go_to_login
        self.login_to_account["font"] = 20
        self.login_to_account.pack(pady=20)

        self.register_account = tk.Button(self, width=40, height=5)
        self.register_account["text"] = "Register"
        self.register_account["command"] = self.go_to_register
        self.register_account["font"] = 20
        self.register_account.pack(pady=20)

        self.quit_app = tk.Button(self, width=40, height=5)
        self.quit_app["text"] = "Exit"
        self.quit_app["command"] = self.quit
        self.quit_app["font"] = 20
        self.quit_app.pack(pady=20)

    def go_to_login(self):
        self.use_window('login')

    def go_to_register(self):
        self.use_window('register')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)

