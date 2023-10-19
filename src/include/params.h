/*
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>

  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef MOS_PARAMS_H
#define MOS_PARAMS_H

// The FUSE API has been changed a number of times.  So, our code
// needs to define the version of the API that we assume.  As of this
// writing, the most current API version is 26
#define FUSE_USE_VERSION 26

// need this to get pwrite().  I have to use setvbuf() instead of
// setlinebuf() later in consequence.
#define _XOPEN_SOURCE 500

// maintain mos state in here
#include <limits.h>
#include <stdio.h>
struct mos_state
{
  FILE * logfile;
  char * rootdir;
};
#define MOS_DATA ((struct mos_state *)fuse_get_context()->private_data)

#endif
