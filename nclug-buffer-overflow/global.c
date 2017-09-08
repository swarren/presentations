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

/*
 * Without using a struct, we can't guarantee the order the variables appear
 * in RAM, which prevents demonstrating the buffer overflow bug.
 */
struct {
    char data[32];
    char cmd[32];
} g;

void get_cmd(void) {
    strcpy(g.cmd, "/bin/ls");
}

void get_data(void) {
    printf("data: ");
    fflush(stdout);
    gets(g.data);
}

void run_cmd(void) {
    system(g.cmd);
}

int main(int argc, char **argv) {
    get_cmd();
    get_data();
    run_cmd();

    return 0;
}

/*
global memory layout:
0x601080 struct g
0x601080 char g.data[]
0x6010a0 char g.cmd[]
*/

/*
$ gdb ./global
(gdb) b get_data
Breakpoint 1 at 0x400662: file global.c, line 15.
(gdb) r
(gdb) p &g.data
$1 = (char (*)[32]) 0x601080 <g>
(gdb) p &g.cmd
$2 = (char (*)[32]) 0x6010a0 <g+32>
(gdb) c
Continuing.
data: 0123456789abcdef0123456789abcdef/bin/sh
(32 chars for data[], new command)
$   <-- shell prompt received
*/
