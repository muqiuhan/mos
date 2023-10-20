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

#ifndef MOS_UNIX_H
#define MOS_UNIX_H

#include "error.h"
#include "result.hpp"

namespace mos::unix
{
  class Filesystem
  {
   public:
    static Result<int, error::Err> Open(const std::string & file, int flag) noexcept;

    static Result<int, error::Err>
    Pread(int fd, char * buffer, size_t nbytes, off_t offset) noexcept;

    static Result<int, error::Err>
    Open(const std::string & file, int flag, int mode) noexcept;
  };
};

#endif /* BONDING_UNIX_H */