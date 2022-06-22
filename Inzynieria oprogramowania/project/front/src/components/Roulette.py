import tkinter as tk
from PIL import ImageTk
from PIL import Image
from random import random
from ..functions.roulette import roulette as roulette_func
from back.UserManager import UserManager

ROULETTE_FILE = "front/global/images/roulette.png"


class Roulette(tk.Frame):
    roulette = None
    spin = None
    back = None
    image_on_canvas = None
    user_manager: UserManager

    def __init__(self, master=None, use_window=None, get_use_mode=None, user_manager=None, get_user_bat=None):
        super().__init__(master)
        self.get_user_bat = get_user_bat
        self.user_manager = user_manager
        self.master = master
        self.use_window = use_window
        self.get_use_mode = get_use_mode

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=30)

        self.roulette = tk.Canvas(self, width=300, height=300)
        self.roulette.pack(pady=20)
        self.roulette["background"] = "#5D5FEF"
        self.image_on_canvas = self.roulette.create_image(150, 150, image=tk.PhotoImage(file=ROULETTE_FILE))

        self.spin = tk.Button(self, width=20, height=2)
        self.spin["text"] = "Spin"
        self.spin["command"] = self.spin_fn
        self.spin["font"] = 20
        self.spin.pack(pady=20)

        self.back = tk.Button(self, width=20, height=2)
        self.back["text"] = "Back"
        self.back["command"] = self.back_fn
        self.back["font"] = 20
        self.back.pack(pady=20)

    def draw(self, end_angle):
        image = Image.open(ROULETTE_FILE)
        angle = 0
        a = 100
        end_angle += 7200
        i = 0
        while angle <= end_angle:
            i = i + 1
            tkimage = ImageTk.PhotoImage(image.rotate(angle))
            self.roulette.itemconfig(self.image_on_canvas, image=tkimage)
            angle += 1 + a
            if angle > 7200 or a <= 0:
                a = 0
            else:
                a -= i * 0.01
            self.update()

    def spin_fn(self):
        if not self.user_manager.bet(self.get_user_bat()):
            self.spin['text'] = "Sry, your account \nis too small :("
            return
        end_angle = random() * 360
        self.draw(end_angle)
        color = roulette_func(end_angle)
        if color == 0:
            self.roulette['background'] = '#00FF00'
            if self.get_use_mode() == 'green':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU WON!")
                self.user_manager.add_account_and_game(self.get_user_bat() * 14, True)

            elif self.get_use_mode() == 'red':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
            else:
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)

        elif color == 1:
            self.roulette['background'] = '#000000'
            if self.get_use_mode() == 'black':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU WON!")
                self.user_manager.add_account_and_game(self.get_user_bat() * 2, True)

            elif self.get_use_mode() == 'red':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
            else:
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
        else:
            self.roulette['background'] = '#FF0000'
            if self.get_use_mode() == 'red':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU WON!")
                self.user_manager.add_account_and_game(self.get_user_bat() * 2, True)

            elif self.get_use_mode() == 'black':
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
            else:
                self.roulette.create_text(150, 150, fill="white", font="Times 40 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
        self.spin["text"] = "Turn back to use color"
        self.spin["command"] = self.back_to_use_color

    def back_fn(self):
        self.use_window('main')

    def back_to_use_color(self):
        self.use_window('play')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
