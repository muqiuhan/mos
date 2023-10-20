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

#ifndef MOS_OPER_H
#define MOS_OPER_H

#include "params.h"
#include <fuse.h>
#include <linux/limits.h>

namespace mos
{

  /** The MOS file system operations */
  class Mos_oper
  {
   private:
    /** File open operation.
     ** The [path] is relative to the root of the mounted file system
     ** and the [file_info] used to maintain information about the file */
    using open_t = int (*)(const char *, int);
    static int open(const char * path, fuse_file_info * file_info) noexcept;

    /** Read data from some specified offset from the beginning of a file. */
    using read_t = int (*)(const char *, char *, size_t, off_t);
    static int read(const char * path,
                    char * buffer,
                    size_t size,
                    off_t offset,
                    fuse_file_info * file_info) noexcept;

    using readdir_t =
      int (*)(const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *);
    static int readdir(const char * path,
                       void * buffer,
                       fuse_fill_dir_t filter,
                       off_t offset,
                       fuse_file_info * file_info) noexcept;

   private:
    /** Translating the relative path  to a full path in the underlying filesystem.
     ** The [full_path] is return value and the [path] is relative path */
    static void full_path(char full_path[PATH_MAX], const char * path) noexcept;

   public:
    /** The fuse callback struct for MOS */
    inline static fuse_operations mos_oper = { .open = open,
                                               .read = read,
                                               .readdir = readdir };
  };
}

#endif /* MOS_OPER_H */