#!/bin/bash

set_led() {
    r=$1
    g=$2
    b=$3
    l=$4
    pdata="red=$r&green=$g&blue=$b&bright=$l"
    wget -O /dev/null --post-data="$pdata" http://192.168.50.1/
}

delay=0.25

set_led 0 0 0 30
sleep $delay
set_led 255 0 0 30
sleep $delay
set_led 0 255 0 30
sleep $delay
set_led 0 0 255 30
sleep $delay
set_led 255 255 255 30
sleep $delay
set_led 255 255 255 60
sleep $delay
set_led 255 255 255 120
sleep $delay
set_led 255 255 255 255
sleep $delay
set_led 0 0 0 30
sleep $delay
