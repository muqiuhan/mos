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

#include "include/unix.h"
#include <fcntl.h>
#include <unistd.h>

/** Auto generate wrapper function for system calls  */
#define GENERATE_SYSTEM_CALL_WRAPPER(OK_TYPE,                                            \
                                     FAILURE_VALUE,                                      \
                                     WRAPPER_FUNCTION_SIGNATURE,                         \
                                     SYSTEM_CALL_FUNCTION_NAME,                          \
                                     ...)                                                \
  Result<OK_TYPE, error::Err> WRAPPER_FUNCTION_SIGNATURE noexcept                        \
  {                                                                                      \
    OK_TYPE SYSTEM_CALL_FUNCTION_RESULT = SYSTEM_CALL_FUNCTION_NAME(__VA_ARGS__);        \
    if (FAILURE_VALUE == SYSTEM_CALL_FUNCTION_RESULT)                                    \
      return ERR(error::Code::System_call);                                              \
    return Ok(SYSTEM_CALL_FUNCTION_RESULT);                                              \
  }

/** Auto generate wrapper function for system calls  */
#define GENERATE_NO_RET_VALUE_SYSTEM_CALL_WRAPPER(OK_TYPE,                               \
                                                  FAILURE_VALUE,                         \
                                                  WRAPPER_FUNCTION_SIGNATURE,            \
                                                  SYSTEM_CALL_FUNCTION_NAME,             \
                                                  ...)                                   \
  Result<Void, error::Err> WRAPPER_FUNCTION_SIGNATURE noexcept                           \
  {                                                                                      \
    OK_TYPE SYSTEM_CALL_FUNCTION_RESULT = SYSTEM_CALL_FUNCTION_NAME(__VA_ARGS__);        \
    if (FAILURE_VALUE == SYSTEM_CALL_FUNCTION_RESULT)                                    \
      return ERR(error::Code::System_call);                                              \
    return Ok(Void());                                                                   \
  }

namespace mos::unix
{
  /** Filesystem::Open */
  GENERATE_SYSTEM_CALL_WRAPPER(int,
                               -1,
                               Filesystem::Open(const std::string & file, int flag),
                               open,
                               file.c_str(),
                               flag);

  /** Filesystem::Open */
  GENERATE_SYSTEM_CALL_WRAPPER(int,
                               -1,
                               Filesystem::Open(const std::string & file,
                                                int flag,
                                                int mode),
                               open,
                               file.c_str(),
                               flag,
                               mode);

  /** Filesystem::Pread */
  GENERATE_SYSTEM_CALL_WRAPPER(
    int,
    -1,
    Filesystem::Pread(int fd, char * buffer, size_t nbytes, off_t offset),
    pread,
    fd,
    buffer,
    nbytes,
    offset);
}