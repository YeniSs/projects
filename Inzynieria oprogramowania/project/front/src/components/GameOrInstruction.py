import tkinter as tk


class GameOrInstruction(tk.Frame):
    play = None
    instruction = None

    def __init__(self, master=None, use_window=None):
        super().__init__(master)
        self.master = master
        self.use_window = use_window

    def create_vue(self):
        self["background"] = "#5D5FEF"
        self.pack(pady=60)
        self.play = tk.Button(self, width=40, height=5)
        self.play["text"] = "Play"
        self.play["command"] = self.go_to_play
        self.play["font"] = 20
        self.play.pack(pady=20)

        self.instruction = tk.Button(self, width=40, height=5)
        self.instruction["text"] = "Instruction"
        self.instruction["command"] = self.go_to_instruction
        self.instruction["font"] = 20
        self.instruction.pack(pady=20)

    def go_to_instruction(self):
        self.use_window('instructions')

    def go_to_play(self):
        self.use_window('play', bet_state=0)

    def clear_vue(self):
        self.destroy()
        super().__init__(self.master)
