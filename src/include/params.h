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

#ifndef MOS_PARAMS_H
#define MOS_PARAMS_H

#include <stdio.h>

namespace mos
{
/** The FUSE API has been changed a number of times.
 ** So, our code needs to define the version of the API that we assume.
 ** As of this writing, the most current API version is 26 */
#define FUSE_USE_VERSION 26

/** Need this to get `pwrite()`.
 ** I have to use `setvbuf()` instead of `setlinebuf()` later in consequence. */
#define _XOPEN_SOURCE 500

  /** Maintain mos state in here */
  struct mos_state
  {
    FILE * logfile;
    char * rootdir;
  };

/** From inside any FUSE operation, it's possible to obtain the context by calling
 ** `fuse_get_context()`; this means we can use `fuse_get_context()->private_data`
 ** to get the private data. */
#define MOS_DATA (reinterpret_cast<mos_state *>(fuse_get_context()->private_data))
}

#endif
