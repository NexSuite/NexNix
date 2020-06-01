# NexNix
NexNix is designed to be a POSIX compliant, UNIX based OS. It aims to run many Unix applications.
# To build
The build system only works on Linux. To build, clone the repository to to NexNix/src in your home folder. Next, open up a command line, and then run . configure --arch=i686. Next, run make, make install, make grub, and lastly make run_grub. You will need a GCC cross compiler for i686-elf, QEMU, KPartx, Parted, make, and grub-pc-bin.
