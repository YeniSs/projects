import tkinter as tk
from ..functions.instructions import switcher


class Instructions(tk.Frame):
    instr = None
    back = None

    def __init__(self, master=None, use_window=None, get_state=None):
        super().__init__(master)
        self.master = master
        self.use_window = use_window
        self.get_state = get_state

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=30)

        self.instr = tk.Label(self, width=500, height=6, wraplength=500)
        state = self.get_state()
        view = switcher(state)
        if view[0][0] == '':
            self.instr['text'] = 'ERROR'
        else:
            self.instr['text'] = view[0][0]
        self.instr["background"] = "#5D5FEF"
        self.instr.pack(pady=20, expand=tk.YES, fill=tk.BOTH)

        self.back = tk.Button(self, width=20, height=2)
        self.back["text"] = "Back"
        self.back["command"] = self.back_fn
        self.back["font"] = 20
        self.back.pack(pady=20)

    def back_fn(self):
        self.use_window('main')

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)

