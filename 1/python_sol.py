with open("input.txt", 'r') as f:
    input_text = f.readlines()

pos = 50
zeros = 0
part_two = True
positions = [50]

for line in input_text:

    if line[0] == 'R':
        turn = int(line[1:])
        # If the non-full-cycle magnitude is enough to cross zero (not including the start)
        if part_two and (turn % 100) > (100 - pos) and pos != 0:
            zeros += 1
    else:
        turn = -1 * int(line[1:])
        # If the non-full-cycle magnitude is enough to cross zero (not including the start)
        if part_two and (int(line[1:]) % 100) > pos and pos != 0:
            zeros += 1

    # For any full cycle we can add one
    if part_two:
        zeros += abs(turn) // 100

    pos = (pos + turn) % 100

    if pos == 0:
        zeros += 1

    positions.append(pos)


print(zeros)