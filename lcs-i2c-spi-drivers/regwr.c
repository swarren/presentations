/*
 * Copyright (c) 2014 Stephen Warren <swarren@wwwdotorg.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned long addr;
	unsigned long addr_aligned;
	unsigned long addr_offset;
	unsigned long *ptr;
	unsigned long value;
	int fd;

	addr = strtoul(argv[1], NULL, 0);
	if (addr & 3 ) {
		fprintf(stderr, "addr misaligned: %x\n", addr);
		return 1;
	}
	addr_aligned = addr & (~(getpagesize() - 1));
	addr_offset = addr - addr_aligned;
	value = strtoul(argv[2], NULL, 0);

	fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		perror("open(/dev/mem) failed");
		return 1;
	}

	ptr = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr_aligned);
	if (ptr == NULL) {
		perror("mmap() failed\n");
		return 1;
	}

	ptr[addr_offset / 4] = value;

	return 0;
}
