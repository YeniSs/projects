import tkinter as tk
import random
from PIL import ImageTk, Image


def spin_first(canvas: tk.Label, time_omg: float, image):
    time_omg['position'] = int(random.random() * 918)
    time_omg['image']['crop_area'] = (0, time_omg['position'], 100, time_omg['position'] + 200)
    time_omg['image']['cropped_image'] = image.crop(time_omg['image']['crop_area'])
    time_omg['save_img_data'] = ImageTk.PhotoImage(image=time_omg['image']['cropped_image'])
    canvas['image'] = time_omg['save_img_data']
    canvas.update()
    while flag(time_omg['is_work'],  time_omg['position'] % 102 != 51):
        time_omg['position'] += 3
        if time_omg['position'] < image.height - 200:
            time_omg['image']['crop_area'] = (0, time_omg['position'], 100, time_omg['position'] + 200)
            time_omg['image']['cropped_image'] = image.crop(time_omg['image']['crop_area'])
        elif time_omg['position'] < image.height:
            time_omg['image']['segment_crop_1'] = (0, time_omg['position'], 100, image.height)
            time_omg['image']['segment_crop_2'] = (0, 0, 100, time_omg['position'] + 200 - image.height)
            time_omg['image']['segment_image_1'] = image.crop(time_omg['image']['segment_crop_1'])
            time_omg['image']['segment_image_2'] = image.crop(time_omg['image']['segment_crop_2'])
            time_omg['image']['cropped_image'] = Image.new('RGB', (100, 200))
            time_omg['image']['cropped_image'].paste(time_omg['image']['segment_image_1'], (0, 0))
            time_omg['image']['cropped_image'].paste(time_omg['image']['segment_image_2'], (0, time_omg['image']['segment_image_1'].height))
        else:
            time_omg['position'] = 0
            time_omg['image']['crop_area'] = (0, time_omg['position'], 100, time_omg['position'] + 200)
            time_omg['image']['cropped_image'] = image.crop(time_omg['image']['crop_area'])
        time_omg['save_img_data'] = ImageTk.PhotoImage(image=time_omg['image']['cropped_image'])
        canvas['image'] = time_omg['save_img_data']


def flag(prop1, prop2):
    if not prop1:
        return prop2
    return prop1


'''
Slots rules:
r1 - r3: 0-8
if r1 == 4 in:
1 - 7
2 - 77
3 - 777
if another r1 == r2 == r3:
0 - 123
1 - 321
2 - 213
3 - 132
5 - 312
6 - 231
7 - 400
8 - 500
'''
def instruction(r1: int, r2: int, r3: int):
    balance = 0
    if r1 == 4 or r2 == 4 or r3 == 4:
        times = 0
        if r1 == 4:
            times += 1
        if r2 == 4:
            times += 1
        if r3 == 4:
            times += 1

        balance = 7 if times == 1 else 77 if times == 2 else 777
    elif r1 == r2 and r2 == r3:
        if r1 == 0:
            balance = 123
        elif r1 == 1:
            balance = 321
        elif r1 == 2:
            balance = 213
        elif r1 == 3:
            balance = 132
        elif r1 == 5:
            balance = 312
        elif r1 == 6:
            balance = 231
        elif r1 == 7:
            balance = 400
        elif r1 == 8:
            balance = 500
    return balance
