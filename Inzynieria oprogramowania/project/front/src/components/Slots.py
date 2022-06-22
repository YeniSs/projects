import copy
import time
import tkinter as tk
from ..functions.slots_spin import spin_first, instruction
from threading import Thread
from back.UserManager import UserManager
from PIL import Image
SLOTS_PATH = 'front/global/images/slots.jpg'
SLOTS_PATH1 = 'front/global/images/slots1.jpg'
SLOTS_PATH2 = 'front/global/images/slots2.jpg'

START_CONFIG = {
    'is_work': True,
    'save_img_data': None,
    'position': None,
    'image': {
        'crop_area': None,
        'cropped_image': None,
        'obj_id': None,
        'segment_crop_1': None,
        'segment_crop_2': None,
        'segment_image_1': None,
        'segment_image_2': None,
    }
}

SLOTS_COST = 50


class Slots(tk.Frame):
    ########################
    # #SLOTS PART
    ########################
    # ##Slots canvases
    first_slot = None
    second_slot = None
    third_slot = None
    # ##Slots images
    image1 = None
    image2 = None
    image3 = None
    # ##Slots threads
    p1 = None
    p2 = None
    p3 = None
    # ##Slots end config
    first_end_config = None
    second_end_config = None
    third_end_config = None
    ########################

    slots_frame = None
    spin_button = None
    back_button = None
    won_label = None
    user_manager: UserManager

    def __init__(self, user_manager: UserManager, master=None, use_window=None):
        super().__init__(master, width=800, height=200)
        self.master = master
        self.use_windows = use_window
        self.image1 = Image.open(SLOTS_PATH)
        self.image2 = Image.open(SLOTS_PATH1)
        self.image3 = Image.open(SLOTS_PATH2)
        self.user_manager = user_manager

    def create_vue(self):
        self.slots_frame = tk.Frame(self.master, width=800, height=400)
        self.slots_frame["background"] = "#5D5FEF"
        self.slots_frame.pack(padx=75, pady=50, side=tk.TOP)

        self.slots_frame.first_slot = tk.Label(self.slots_frame, width=100, height=200)
        self.slots_frame.first_slot.pack(padx=50, side=tk.LEFT)
        self.slots_frame.first_slot.after(1, Thread(target=self.slots_frame.first_slot.update).start())
        self.slots_frame.second_slot = tk.Label(self.slots_frame, width=100, height=200)
        self.slots_frame.second_slot.pack(padx=50, side=tk.LEFT)
        self.slots_frame.second_slot.after(1, Thread(target=self.slots_frame.second_slot.update).start())

        self.slots_frame.third_slot = tk.Label(self.slots_frame, width=100, height=200)
        self.slots_frame.third_slot.pack(padx=50, side=tk.LEFT)
        self.slots_frame.third_slot.after(1, Thread(target=self.slots_frame.third_slot.update).start())

        self.first_slot = self.slots_frame.first_slot
        self.second_slot = self.slots_frame.second_slot
        self.third_slot = self.slots_frame.third_slot

        self.spin_button = tk.Button(self, width=300, height=3)
        self.spin_button["text"] = "Spin"
        self.spin_button["command"] = self.start_spin_animation
        self.spin_button["font"] = 20
        self.spin_button.pack(padx=100, side=tk.TOP)

        self.back_button = tk.Button(self, width=300, height=3)
        self.back_button["text"] = "Back"
        self.back_button["command"] = self.go_back
        self.back_button["font"] = 20
        self.back_button.pack(padx=100, side=tk.TOP)

        self["background"] = "#5D5FEF"
        self.pack(padx=150, pady=50)
        self.won_label = tk.Label(self, width=300, height=3)
        self.won_label.pack(padx=100, side=tk.TOP)
        self.start_spin_animation()

    def start_spin_animation(self):
        self.first_end_config = copy.deepcopy(START_CONFIG)
        self.second_end_config = copy.deepcopy(START_CONFIG)
        self.third_end_config = copy.deepcopy(START_CONFIG)
        self.p1 = Thread(target=spin_first, args=(self.first_slot, self.first_end_config, self.image1))
        self.p2 = Thread(target=spin_first, args=(self.second_slot, self.second_end_config, self.image2))
        self.p3 = Thread(target=spin_first, args=(self.third_slot, self.third_end_config, self.image3))

        self.p1.start()
        self.p2.start()
        self.p3.start()
        if self.user_manager.check_account() < SLOTS_COST:
            self.spin_button["text"] = "Ops, your balance \nis too small :("
            self.spin_button['command'] = None
        else:
            self.spin_button["text"] = "Spin"
            self.spin_button['command'] = self.spin_method
        self.spin_button.update()
        self.won_label["text"] = 'Your balance: ' + str(self.user_manager.check_account())
        self.won_label.update()

    def spin_method(self):
        self.spin_button['command'] = None
        self.user_manager.currentUser.change_account(-SLOTS_COST)
        Thread(target=self.stop_slots).start()

    def stop_slots(self):
        self.first_end_config['is_work'] = False
        self.first_slot['image'] = self.first_end_config['save_img_data']
        self.first_slot.update()
        time.sleep(1)
        self.second_end_config['is_work'] = False
        self.second_slot['image'] = self.first_end_config['save_img_data']
        self.second_slot.update()
        time.sleep(1)
        self.third_end_config['is_work'] = False
        self.third_slot['image'] = self.first_end_config['save_img_data']
        self.third_slot.update()
        time.sleep(1)
        get_money = instruction(int(self.first_end_config['position'] / 102),
                                int(self.second_end_config['position'] / 102),
                                int(self.third_end_config['position'] / 102))
        self.user_manager.add_account_and_game(get_money, False if get_money == 0 else True)
        self.won_label["text"] = 'You won: ' + str(get_money)
        self.won_label.update()
        self.spin_button["text"] = "Spin one more time"
        self.spin_button["command"] = self.start_spin_animation
        self.spin_button.update()

    def go_back(self):
        self.clear_vue()
        self.use_windows('main')

    def clear_vue(self):
        self.destroy()
        self.slots_frame.destroy()
        self.p1.join(1)
        self.p1.join(2)
        self.p1.join(3)
        super().__init__(self.master)