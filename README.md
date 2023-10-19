<div align="center">

# MOS

*A minimalist file system implementation based on FUSE*

</div>

## Introduction

<div align="center">

![](.github/fuse.webp)

</div>

To simply understand: FUSE implements a callback for file system access. FUSE is divided into two parts: kernel-mode modules and user-mode libraries. Among them, the user-mode library provides interfaces for program development, which are also the interfaces we use during actual development. We register the request processing function into FUSE through these interfaces. The kernel-mode module is the implementation of specific data processing. It intercepts file access requests and then calls functions registered in user mode for processing.

## Reference
- [IBM: Develop your own filesystem with FUSE](http://www.cs.williams.edu/~jannen/teaching/s19/cs333/readings/FUSE/IBM_l-fuse.pdf)
- [FUSE - The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/filesystems/fuse.html)
- [ArchWiki: FUSE](https://wiki.archlinux.org/title/FUSE)
- [libfuse API documentation](http://libfuse.github.io/doxygen/)
- BBFS by Joseph J. Pfeiffer, Jr., Ph.D. 

## Build
> This project is built using [xmake](https://xmake.io)

- Build: `xmake build`
- Instal: `xmake install`

## Usage

Mount a MOS filesystem by running the command `mos` (in general, a FUSE filesystem is implemented by a program, and you mount it by running that program): `mos rootdir mountdir`
   > The root directory (which contains the actual directory data) and the mount directory. 

Every time you perform any file operation in mountdir, the operation (and a whole bunch of both relevant and irrelevant stuff) gets logged to a new file in the current working directory called `mos.log`

## LICENSE
The MIT License (MIT)

Copyright (c) 2023 Muqiu Han

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.