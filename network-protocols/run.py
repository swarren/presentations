#!/usr/bin/python3

# Copyright (c) 2017, Stephen Warren
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

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

slides = ['']
fnum = 0
prev_fnum = 0

def change_fn(new_fnum):
    global prev_fnum
    global fnum
    prev_fnum = fnum
    fnum = new_fnum
    if fnum < 0:
        fnum = 0
    if fnum >= len(slides):
        fnum = len(slides) - 1
    render()

def render():
    header = ''
    body = slides[fnum].strip()
    footer = '\r\n\r\n~~~ SLIDE ' + str(fnum) + '/' + str(len(slides) - 1) + '\r\n'

    erase = chr(27) + '[2J'
    home = chr(27) + '[0;0H'
    sys.stdout.write(erase + home + header + body + footer)

def split_render():
    with open('presentation.txt', 'rt') as f:
        lines = f.readlines()

    del slides[:]
    for line in lines:
        if line.strip() == '--- SLIDE ---':
            slides.extend([''])
            continue
        if slides:
            slides[-1] = slides[-1] + line

    render()

def main():
    split_render()
    while True:
        c = getch()
        if c == 'q':
            break
        elif c == 'n':
            change_fn(fnum + 1)
        elif c == 'p':
            change_fn(fnum - 1)
        elif c == 's':
            split_render()
        elif c == 'r':
            render()
        elif c == '0':
            change_fn(0)
        elif c == '-':
            change_fn(prev_fnum)

main()
