import tkinter as tk
import os
import time
from threading import Thread

from back.UserManager import UserManager
from ..functions.coin_flip import flip as flip_func

COIN_FLIP_GIF = "front/global/images/flip.gif"
COIN_TIMES = 11
RESULT = 2
COUNTER = 1

class CoinFlip(tk.Frame):
    coin_flip = None
    flip = None
    back = None
    user_manager: UserManager

    def __init__(self, user_manager: UserManager, master=None, use_window=None, get_use_mode=None, get_user_bat=None):
        super().__init__(master)
        self.user_manager = user_manager
        self.master = master
        self.use_window = use_window
        self.get_use_mode = get_use_mode
        self.get_user_bat = get_user_bat
        self.coin_flip_gif = [tk.PhotoImage(file=(os.path.expanduser("front/global/images/flip.gif")),format = 'gif -index %i' % (i)) for i in range(COIN_TIMES)]

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=30)

        self.coin_flip = tk.Canvas(self, width=300, height=300)
        character = self.coin_flip.create_image((0, 0), image=self.coin_flip_gif[0], anchor=tk.NW)
        self.coin_flip.pack(pady=20, expand=tk.YES, fill=tk.BOTH)
        self.coin_flip["background"] = "#5D5FEF"

        self.flip = tk.Button(self, width=20, height=2)
        self.flip["text"] = "Flip"
        self.flip["command"] = self.flip_fn
        self.flip["font"] = 20
        self.flip.pack(pady=20)

        self.back = tk.Button(self, width=20, height=2)
        self.back["text"] = "Back"
        self.back["command"] = self.back_fn
        self.back["font"] = 20
        self.back.pack(pady=20)

    def draw(self, RESULT):
        if RESULT == 0:
            if self.get_use_mode() == 'heads':
                self.coin_flip.create_text(150, 10, fill="red", font="Times 20 italic bold",
                                        text="YOU WON!")
                self.user_manager.add_account_and_game(self.get_user_bat() * 2, True)
            else:
                self.coin_flip.create_text(150, 10, fill="red", font="Times 20 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)
        else:
            if self.get_use_mode() == 'tails':
                self.coin_flip.create_text(150, 10, fill="red", font="Times 20 italic bold",
                                        text="YOU WON!")
                self.user_manager.add_account_and_game(self.get_user_bat() * 2, True)
            else:
                self.coin_flip.create_text(150, 10, fill="red", font="Times 20 italic bold",
                                        text="YOU LOST")
                self.user_manager.add_account_and_game(0, False)

    def flip_fn(self):
        if self.user_manager.bet(self.get_user_bat()):
            Thread(target=self.flip_fn_async).start()
        else:
            self.flip['text'] = "Sorry, your account \nis too small :("

    def flip_fn_async(self):
        RESULT = flip_func()
        character = self.coin_flip.create_image((0, 0), image=self.coin_flip_gif[0], anchor=tk.NW)
        self.coin_flip.itemconfig(character, image=self.coin_flip_gif[0])
        self.after(0, self.update_coin, 0, 0, RESULT)
        self.coin_flip.update()
        if RESULT == 0:
            time.sleep(6.5)
        else:
            time.sleep(7)
        self.draw(RESULT)
        self.flip["text"] = "Turn back to choose side"
        self.flip["command"] = self.back_to_choose_side

    def back_fn(self):
        self.use_window('main')

    def back_to_choose_side(self):
        self.use_window('play')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)

    def update_coin(self, index, COUNTER, RESULT):
        frame = self.coin_flip_gif[index]
        index += 1
        COUNTER += 1
        if index >= COIN_TIMES:
            index = 0
        if RESULT == 0:
            if COUNTER != 101:
                self.coin_flip.delete('all')
                self.coin_flip.create_image((0, 0), image=frame, anchor=tk.NW)
                self.after(COUNTER, self.update_coin, index, COUNTER, RESULT)
        if RESULT == 1:
            if COUNTER != 107:
                self.coin_flip.delete('all')
                self.coin_flip.create_image((0, 0), image=frame, anchor=tk.NW)
                self.after(COUNTER, self.update_coin, index, COUNTER, RESULT)


