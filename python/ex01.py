from turtle import *

hideturtle()
speed(0)

line = 1
angle = 180

min = 0
max = 180

colormode(255)

for i in range(min, max):
    i += 1

    tup = (i, i, i)
    pencolor(tup)

    forward(line)
    left(angle)
    angle -= 1
    line += 2

input();