from .components.GameUse import GameUse
from .components.Main import Main
from .components.BetOrLearn import BetOrLearn
from .components.Bet import Bet
from .components.GameOrInstruction import GameOrInstruction
from .components.CoinUse import CoinUse
from .components.RouletteUse import RouletteUse
from .components.Roulette import Roulette
from .components.CoinFlip import CoinFlip
from .components.Slots import Slots
from back.UserManager import UserManager, User
from .components.Instructions import Instructions
from .components.Desktop import Desktop
from .components.Register import Register
from .components.Login import Login
from .components.TopUp import TopUp
import tkinter as tk


class Routing:
    game_use: None or GameUse = None
    bet_or_learn: None or BetOrLearn = None
    bet: None or Bet = None
    main: None or Main = None
    game_or_instruction: None or GameOrInstruction = None
    coin_use: None or CoinUse = None
    roulette_use: None or RouletteUse = None
    roulette: None or Roulette = None
    coin_flip: None or CoinFlip = None
    slots: None or Slots = None
    instructions: None or Instructions = None

    current_window: None or tk.Frame = None
    state: None or str = None
    mode: None or str = None
    bet_state: None or str = None
    use_mode: None or str = None
    user: None or User = None
    user_manager: None or UserManager = None

    def __init__(self, master=None):
        self.user_manager = UserManager()

        self.game_use = GameUse(master=master, use_window=self.use_window)
        self.bet_or_learn = BetOrLearn(master=master, use_window=self.use_window)
        self.main = Main(user_manager=self.user_manager, master=master, use_window=self.use_window)
        self.bet = Bet(master=master, use_window=self.use_window, user_balance=self.user_manager.bet)
        self.game_or_instruction = GameOrInstruction(master=master, use_window=self.use_window)
        self.coin_use = CoinUse(master=master, use_window=self.use_window)
        self.roulette_use = RouletteUse(master=master, use_window=self.use_window)
        self.instructions = Instructions(master=master, use_window=self.use_window, get_state=self.get_state)
        self.desktop = Desktop(master=master, use_window=self.use_window)
        self.register = Register(master=master, use_window=self.use_window, user_manager=self.user_manager)
        self.login = Login(user_manager=self.user_manager, master=master, use_window=self.use_window)
        self.topup = TopUp(user_manager=self.user_manager, master=master, use_window=self.use_window)

        self.master = master

    def start(self):
        self.current_window = self.desktop
        self.current_window.create_vue()
        self.current_window.mainloop()

    def get_state(self):
        return self.state

    def get_mode(self):
        return self.mode

    def get_use_mode(self):
        return self.use_mode

    def get_user(self):
        return self.user

    def get_user_bat(self):
        return self.bet_state

    def set_user(self):
        self.roulette = Roulette(master=self.master,
                                 use_window=self.use_window,
                                 get_use_mode=self.get_use_mode,
                                 user_manager=self.user_manager,
                                 get_user_bat=self.get_user_bat
                                 )
        self.coin_flip = CoinFlip(master=self.master,
                                 use_window=self.use_window,
                                 get_use_mode=self.get_use_mode,
                                 user_manager=self.user_manager,
                                 get_user_bat=self.get_user_bat
                                 )
        self.slots = Slots(master=self.master,
                                 use_window=self.use_window,
                                 user_manager=self.user_manager
                                 )

    def use_window(self, window_name="", state=None, loggin_correct=None, mode=None, use_mode=None, bet_state=None):
        if state is not None:
            self.state = state
        if mode is not None:
            self.mode = mode
        if use_mode is not None:
            self.use_mode = use_mode
        if bet_state is not None:
            self.bet_state = bet_state
        if loggin_correct is not None:
            self.set_user()

        if self.current_window is not None:
            self.current_window.clear_vue()
        if window_name == 'desktop':
            self.current_window = self.desktop
        elif window_name == 'login':
            self.current_window = self.login
        elif window_name == 'register':
            self.current_window = self.register
        elif window_name == 'topup':
            self.current_window = self.topup
        elif window_name == 'game_use':
            self.current_window = self.game_use
        elif window_name == 'bet_or_learn' and self.get_state() == 'slots':
            self.current_window = self.game_or_instruction
        elif window_name == 'bet_or_learn':
            self.current_window = self.bet_or_learn
        elif window_name == 'main':
            self.current_window = self.main
        elif window_name == 'bet':
            self.current_window = self.bet
        elif window_name == 'game_or_instruction':
            self.current_window = self.game_or_instruction
        elif window_name == 'instructions':
            self.current_window = self.instructions
        elif window_name == 'play' and self.get_state() == 'slots':
            self.current_window = self.slots
        elif window_name == 'play' and self.get_state() is not None:
            if self.get_state() == 'coin_flip':
                self.current_window = self.coin_use
            elif self.get_state() == 'roulette':
                self.current_window = self.roulette_use
        elif window_name == 'coin_flip':
            self.current_window = self.coin_flip
        elif window_name == 'roulette':
            self.current_window = self.roulette
        else:
            self.current_window = self.main
        self.current_window.create_vue()
        self.current_window.mainloop()