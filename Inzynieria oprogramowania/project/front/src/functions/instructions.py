from back.RouletteInstruction import RouletteInstruction
from back.CoinFlipInstruction import CoinFlipInstruction
from back.SlotsInstruction import SlotsInstruction


def switcher(instruct: str):
    if instruct == 'coin_flip':
        return CoinFlipInstruction().view()
    elif instruct == 'slots':
        return SlotsInstruction().view()
    elif instruct == 'roulette':
        return RouletteInstruction().view()

