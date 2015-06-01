#!/usr/bin/python3

import os
import shutil

os.system('rm *.scad')
os.system('rm *.txt')

f = open('all-data', 'rt')
lines = f.readlines()
f.close()

def open_notes():
    global fo
    global fnum
    fnum += 1
    fo = open('gen-' + str(fnum) + '.txt', 'wt')

def open_code():
    global fo
    fo = open('gen-' + str(fnum) + '.scad', 'wt')

fnum = -1
fo = None
in_notes = True
for line in lines:
    if line.strip() == 'NOTES:':
        if in_notes:
            open_code()
        if fo:
            fo.close()
        in_notes = True
        open_notes()
        continue
    if line.strip() == 'CODE:':
        if not in_notes:
            open_notes()
        if fo:
            fo.close()
        in_notes = False
        open_code()
        continue
    if line.strip().startswith('INCLUDE:'):
        incfn = line.split(':')[1].strip()
        fi = open(incfn, 'rt')
        shutil.copyfileobj(fi, fo)
        fi.close()
        continue
    fo.write(line)
if fo:
    fo.close()
