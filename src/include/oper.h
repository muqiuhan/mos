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

#include <fuse/fuse.h>
#include <linux/limits.h>

namespace mos
{

  /**
   * @brief The MOS file system operations
   */
  class Mos_oper
  {
   private:
    /**
     * @brief File open operation
     * @param path Relative to the root of the mounted file system
     * @param file_info Used to maintain information about the file
     * @return -1 is returned and errno is set to indicate the error.
     */
    using open_t = int (*)(const char *, int);
    static int open(const char * path, fuse_file_info * file_info) noexcept;

    /**
     * @brief Read data from some specified offset from the beginning of a file.
     * @return @param buffer
     */
    using read_t = int (*)(const char *, char *, size_t, off_t);
    static int read(const char * path,
                    char * buffer,
                    size_t size,
                    off_t offset,
                    fuse_file_info * file_info) noexcept;

   private:
    /**
     * @brief  Translating the relative path  to a full path in the underlying filesystem.
     * @param full_path The return value
     * @param path The relative path
     */
    static void full_path(char full_path[PATH_MAX], const char * path) noexcept;

   public:
    /**
     * @brief The fuse callback struct for MOS
     */
    inline static fuse_operations mos_oper = { .open = reinterpret_cast<open_t>(open),
                                               .read = reinterpret_cast<read_t>(read) };
  };
}

#endif /* MOS_OPER_H */