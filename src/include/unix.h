/** Copyright (C) 2023 Muqiu Han <muqiu-han@outlook.com> */

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
    Open(const std::string & file, int flag, int mode) noexcept;
  };
};

#endif /* BONDING_UNIX_H */