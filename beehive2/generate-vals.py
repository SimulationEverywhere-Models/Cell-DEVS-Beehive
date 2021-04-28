import random
import sys

# Percentage of space filled with bees to study movement in different sized groups
bee_space = 0.30
# The placement of the casu robots(row,col)
casu_robots = [(25,12),(25, 37)]
casu_size = (2,2)
casu_robot_temp = 5 # 1 < t < 9
# Dimensions of cell space
width = 50
height = 50
# Ambient temp for a single bee
ambient_temp = 29

# Whether to add walls and barrier in the center
gen_perimeter = True
center_wall = True

for i in range(round(bee_space * width * height)):
    print("(" + str(random.randint(0,width)) + "," + str(random.randint(0,height)) + ")=" + str(ambient_temp) + "1" + str(random.randint(1,8)))

# Generate CASU robots to control local temperature
for robot in casu_robots:
    for row in range(casu_size[0]):
        for col in range(casu_size[1]):
            print("(" + str(robot[0] + row) + "," + str(robot[1] + col) + ")=" + "50" + str(casu_robot_temp) + "9")

# Generate center wall
for i in range(height):
    print("(" + str(i) + "," + str(round(width/2)) + ")=" + "9909")

# # Generate walls around perimeter
if gen_perimeter:
    for i in range(width):
        print("(0," + str(i) + ")=" + "9909")
        print("(" + str(height - 1) + "," + str(i) + ")=" + "9909")
    for i in range(height):
        print("(" + str(i) + ",0)=" + "9909")
        print("(" + str(i) + "," + str(width - 1) + ")=" + "9909")
    print("(0,0)=9909")
else:
    print("(0,0)=2800")

# Last print statement needed to avoid an error