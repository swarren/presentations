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

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct i2c_smbus_ioctl_data ids = {
	.read_write = I2C_SMBUS_WRITE,
	.command = 0,
	.size = I2C_SMBUS_QUICK,
};

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int i;
	unsigned int sts,  h, t;
	float hf, tf;
	unsigned char buf[4];

	fd = open("/dev/i2c-1", O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "Failed to open device node\n");
		exit(1);
	}

	ret = ioctl(fd, I2C_SLAVE, 0x27);
	if (ret < 0) {
		fprintf(stderr, "Failed to set I2C address\n");
		exit(1);
	}

	ret = ioctl(fd, I2C_SMBUS, &ids);
	if (ret != 0) {
		fprintf(stderr, "ioctl(ids) failed: %d\n", ret);
		exit(1);
	}

	usleep(50 * 1000);

	ret = read(fd, buf, 4);
	if (ret != 4) {
		fprintf(stderr, "read() failed: %d\n", ret);
		exit(1);
	}

	for (i = 0; i < 4; i++) {
		printf("%02x\n", buf[i]);
	}

	sts = buf[0] >> 6;
	h = ((buf[0] & 0x3f) << 8) | buf[1];
	t = (buf[2] << 6) | (buf[3] >> 2);

	switch (sts) {
	case 0:
		printf("Valid data:\n");
		break;
	case 1:
		printf("Stale data:\n");
		break;
	case 2:
		printf("Command Mode!\n");
		return 1;
	case 3:
		printf("Diagnostic Mode!\n");
		return 1;
	}

	hf = h;
	hf *= 100;
	hf /= (1 << 14) - 1;
	printf("Humidity: %.1f%%\n", hf);

	tf = t;
	tf /= (1 << 14) - 1;
	tf *= 165;
	tf -= 40;
	printf("Temperature: %.1fC\n", tf);

	tf *= (9.0 / 5);
	tf += 32;
	printf("Temperature: %.1fF\n", tf);

	return 0;
}
