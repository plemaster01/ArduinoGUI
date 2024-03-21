import math
import time
from math import cos, sin

import serial
import pygame

pygame.init()

WIDTH = 400
HEIGHT = 400
screen = pygame.display.set_mode([WIDTH, HEIGHT])

arduinoData = serial.Serial('com19', 115200)
timer = pygame.time.Clock()
fps = 60
data = [0, 0, 0, 0, 0]
font = pygame.font.Font('freesansbold.ttf', 24)


def parseData(input):
    # sample input b'00000\r\n' - servo at 0 degrees and b'0000180\r\n - servo at 180 degrees'
    # this function takes the raw 12-14 character string and parses it into the five integer values desired
    out = []  # led bank1,2,3 and 4 then servo angle
    nums = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    ang = input[6:-5]
    for i in range(len(ang)):
        if ang[i] not in nums:
            ang = 0
    if ang == '':
        ang = 0
    ang = int(ang)
    st1 = input[2]
    if st1 not in nums:
        st1 = 0
    else:
        st1 = int(st1)
    st2 = input[3]
    if st2 not in nums:
        st2 = 0
    else:
        st2 = int(st2)
    st3 = input[4]
    if st3 not in nums:
        st3 = 0
    else:
        st3 = int(st3)
    st4 = input[5]
    if st4 not in nums:
        st4 = 0
    else:
        st4 = int(st4)
    out = [ang, st1, st2, st3, st4]
    return out


def draw_screen(ins):
    radius = 90
    # point one at 200, 90
    xprime = 200 - radius * cos(ins[0] / 57.2958)
    yprime = 90 - radius * sin(ins[0] / 57.2958)
    screen.blit(font.render(f'angle: {ins[0]}*', True, 'dark gray'), (190, 10))
    pygame.draw.line(screen, 'white', (200, 90), (xprime, yprime), 10)
    pygame.draw.circle(screen, 'dark gray', (200, 90), 10)

    change = ['-5', '-10', '+5', '+10']

    for i in range(4):
        if ins[i + 1] == 3:
            pygame.draw.circle(screen, 'red', (50 + 100 * i, 160), 40)
            pygame.draw.circle(screen, 'green', (50 + 100 * i, 250), 40)
            pygame.draw.circle(screen, 'white', (50 + 100 * i, 340), 40)
        elif ins[i + 1] == 2:
            pygame.draw.circle(screen, 'red', (50 + 100 * i, 160), 40)
            pygame.draw.circle(screen, 'green', (50 + 100 * i, 250), 40)
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 340), 40)
        elif ins[i + 1] == 1:
            pygame.draw.circle(screen, 'red', (50 + 100 * i, 160), 40)
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 250), 40)
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 340), 40)
        else:
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 160), 40)
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 250), 40)
            pygame.draw.circle(screen, 'dark gray', (50 + 100 * i, 340), 40)
        screen.blit(font.render(f'{change[i]}', True, 'white'), (30 + 100 * i, 97))


# main repeating loop where we check for new arduino data and display onto a GUI if we have good new data
run = True
while run:
    screen.fill('black')
    # timer.tick(fps)
    if arduinoData.inWaiting() == 0:
        pass
    dataPacket = arduinoData.readline()
    dataPacket = str(dataPacket)
    print(dataPacket)
    if len(dataPacket) in [12, 13, 14]:
        data = parseData(dataPacket)
    draw_screen(data)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    pygame.display.flip()
pygame.quit()
