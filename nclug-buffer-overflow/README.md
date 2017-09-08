The code in this directory demonstrates some of the most trivial kinds of
buffer overflow bugs. The code is contrived, in particular relying on the
dangerous deprecated function gets() to overflow buffers. The intent is to
demonstrate what can happen when buffers are overflowed, rather than
concentrating on bugs that can allow buffers to be overflowed. Some of the
overflows can be easily prevented or made unreliable by enabling (actually, not
disabling) compiler and operating system features such as stack cookies and
ASLR (Address Space Layout Randomization).
