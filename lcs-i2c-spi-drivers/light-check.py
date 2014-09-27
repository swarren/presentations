#!/usr/bin/env python2

# Copyright (c) 2014 Stephen Warren <swarren@wwwdotorg.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import os
import sys

fn_lock = '/tmp/light-check-lock'
fn_history = '/tmp/light-check-history'
fn_sensor = '/sys/bus/i2c/drivers/tsl2563/1-0039/iio:device0/in_intensity_both_raw'

try:
    fd = os.open(fn_lock, os.O_CREAT | os.O_EXCL, 0700)
    os.close(fd)
except:
    print "Locked; exiting"
    sys.exit(1)

try:
    f = file(fn_sensor, 'rt')
    level_text = f.read()
    f.close()

    level = int(level_text)
    light_on = str(level > 25)

    try:
        f = file(fn_history, 'rt')
        prev_light_on = f.read()
        f.close()
    except:
        prev_light_on = str(0 == 1)

    if light_on != prev_light_on:
        print 'LIGHT STATUS CHANGE, now', light_on

        f = file(fn_history, 'wt')
        f.write(light_on)
        f.close()
finally:
    os.unlink(fn_lock)
