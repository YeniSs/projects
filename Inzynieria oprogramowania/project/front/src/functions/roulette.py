def roulette(spin_degree):
    total_degree = 360.0
    roulette_slots = 38
    divide_to_cells = total_degree / roulette_slots
    randomized_cell = spin_degree / divide_to_cells
    randomized_cell = int(randomized_cell)
    if randomized_cell == 0 or randomized_cell == 37:
        return 0  # green
    elif randomized_cell % 2 == 0:
        return 1  # black
    elif randomized_cell % 2 == 1:
        return 2  # red
