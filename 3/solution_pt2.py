with open("input.txt", 'r') as f:
    lines = f.readlines()

run_sum = 0
digits_needed = 12


for line in lines:
    bat = line[:-1]
    
    chosen_digits = []
    earliest_index_avail = 0

    for i in range(digits_needed):

        digits_to_right = digits_needed - 1 - i

        right_slice = None if digits_to_right == 0 else -1 * digits_to_right

        available_digits = bat[earliest_index_avail:right_slice]

        max_digit_choice = max([int(x) for x in available_digits])
        max_digit_index = available_digits.index(str(max_digit_choice))
        earliest_index_avail = max_digit_index + earliest_index_avail + 1

        chosen_digits.append(str(max_digit_choice))
    
    run_sum += int("".join(chosen_digits))
    
    print(bat, chosen_digits)

print("Total: ", run_sum)