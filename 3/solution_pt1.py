with open("input.txt", 'r') as f:
    lines = f.readlines()

run_sum = 0

for line in lines:
    bat = line[:-1]
    max_first_digit = max([int(x) for x in bat[:-1]])
    index_of_max = bat.index(str(max_first_digit))

    max_second_digit = max([int(x) for x in bat[index_of_max+1:]])

    bat_value = int(str(max_first_digit) + str(max_second_digit))
    run_sum += bat_value

print("Total: ", run_sum)