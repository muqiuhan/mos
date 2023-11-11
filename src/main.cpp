/**
 * Copyright (C) 2023 Muqiu Han <muqiu-han@outlook.com?
 *
 * This program can be distributed under the terms of the GNU GPLv3.
 * See the file COPYING.
 *
 * Since the point of this filesystem is to learn FUSE and its
 * datastructures, I want to see *everything* that happens related to
 * its data structures.  This file contains macros and functions to
 * accomplish this. */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
int
main(int argc, char ** argv)
{
  const char * root_dir = argv[1];
  const char * mount_dir = argv[2];

  /* In root, any user making use of the filesystem has root privileges on that
   * filesystem, If the process has access to the actual filesystem, this could easily be
   * used to gain pretty much unlimited access. MOS does not allow root to mount the
   * filesystem */
  if ((getuid() == 0) || (geteuid() == 0))
    {
      std::cerr << "Running BBFS as root opens unnacceptable security holes" << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
