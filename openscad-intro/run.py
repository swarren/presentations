#!/usr/bin/python3

import os
import shutil
import sys
import termios
import tty

def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

fnum = 0

def change_fn(incr):
    global fnum
    if incr:
        fnum += 1
    else:
        if fnum > 0:
            fnum -= 1

    render()

def render():
    fname_scad = 'gen-' + str(fnum) + '.scad'
    fname_notes = 'gen-' + str(fnum) + '.txt'

    basetext = 'INDEX ' + str(fnum) + '\r\n\r\n'

    try:
        shutil.copyfile(fname_scad, 'gen-current.scad')
        etext = ''
    except:
        etext = 'SCAD FILE COPY FAILURE\r\n'

    try:
        f = open(fname_notes, 'rt')
        notes = f.read().strip()
        f.close()
    except:
        notes = 'NOTES READ FAILURE\r\n'

    erase = chr(27) + '[2J'
    home = chr(27) + '[0;0H'
    sys.stdout.write(erase + home + basetext + etext + notes)

def split_render():
    os.system('./split.py')
    render()

def loop():
    split_render()
    while True:
        c = getch()
        if c == 'q':
            break
        elif c == 'n':
            change_fn(incr = True)
        elif c == 'p':
            change_fn(incr = False)
        elif c == 's':
            split_render()
        elif c == 'r':
            render()

loop()    
