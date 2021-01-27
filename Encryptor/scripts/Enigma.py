import random

first = list(range(0, 256))
random.shuffle(first)
second = list(range(0, 256))
random.shuffle(second)
third = list(range(0, 256))
random.shuffle(third)

firstReverse = [None for _ in range(256)]
for num, value in enumerate(first, start=0):
    firstReverse[value] = num

secondReverse = [None for _ in range(256)]
for num, value in enumerate(second, start=0):
    secondReverse[value] = num

thirdReverse = [None for _ in range(256)]
for num, value in enumerate(third, start=0):
    thirdReverse[value] = num

reflector = [None for _ in range(256)]
randomForReflector = list(range(0, 256))
random.shuffle(randomForReflector)

for i in range(0, 256, 2):
    reflector[randomForReflector[i]] = randomForReflector[i + 1]
    reflector[randomForReflector[i + 1]] = randomForReflector[i]

print("static const unsigned char first[256] {" + (", ".join(map(str, first))) + "};")
print("static const unsigned char firstReverse[256] {" + (", ".join(map(str, firstReverse))) + "};")
print("static const unsigned char second[256] {" + (", ".join(map(str, second))) + "};")
print("static const unsigned char secondReverse[256] {" + (", ".join(map(str, secondReverse))) + "};")
print("static const unsigned char third[256] {" + (", ".join(map(str, third))) + "};")
print("static const unsigned char thirdReverse[256] {" + (", ".join(map(str, thirdReverse))) + "};")
print("static const unsigned char reflector[256] {" + (", ".join(map(str, reflector))) + "};")
