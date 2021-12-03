# Part 1
with open('day1-inputs.dat', 'r') as file:
    inputs = [int(line) for line in file]

count = 0
for i, elem in enumerate(inputs[:-1]):
    if elem < inputs[i+1]:
        count += 1   

print(f'Part 1: {count=}')

# Part 2

def sum_three_measurements(index):
    return (
          inputs[index]
        + inputs[index+1]
        + inputs[index+2] 
        )

count = 0
for i in range(len(inputs) - 3):
    if sum_three_measurements(i) < sum_three_measurements(i+1):
        count += 1

print(f'Part 2: {count=}')
