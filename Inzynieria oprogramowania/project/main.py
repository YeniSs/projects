import tkinter as tk
from front.src.routing import Routing

def main():
    root = tk.Tk()
    root.resizable(width=False, height=False)
    root["background"] = "#5D5FEF"
    root.title('Casino')
    root.geometry('800x600')
    routing = Routing(master=root)
    routing.start()
    print('exit')


if __name__ == '__main__':
    main()
