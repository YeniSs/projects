import random

def flip():
    num = random.randint(0, 1)
    if num == 0:
        return 0  # heads
    else:
        return 1  # tails