/*
 * Copyright (c) 2017, Stephen Warren
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_if_authorized(void) {
    char cmd[] = "/bin/ls";
    char data[32];

    printf("data: ");
    fflush(stdout);
    gets(data);

    system(cmd);
}

int main(int argc, char **argv) {
    run_if_authorized();
    return 0;
}

/*
run_if_authorized() stack frame:
var     offset  size
cmd[]       32     8
data[]       0    32  <-- stack pointer
*/

/*
$ gdb ./stack-var-flag
(gdb) b 9
(gdb) r
(gdb) p &cmd
$1 = (char (*)[8]) 0x7fffffffe0f0
(gdb) p &data
$2 = (char (*)[32]) 0x7fffffffe0d0
(gdb) c
Continuing.
data: 01234567890123456789012345678901/bin/sh
(32 chars for data[], new command)
$   <-- shell prompt received
*/
