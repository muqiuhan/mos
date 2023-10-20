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

#include "./include/oper.h"
#include "./include/log.h"
#include "./include/unix.h"
#include <cstring>
#include <dirent.h>
#include <linux/limits.h>
#include <unistd.h>

namespace mos
{

  void
  Mos_oper::full_path(char full_path[PATH_MAX], const char * path) noexcept
  {
    strcpy(full_path, MOS_DATA->rootdir);
    strncat(full_path, path, PATH_MAX);

    log_msg("Mos_oper::full_path: rootdir = %s, path = %s, full_path = %s\n",
            MOS_DATA->rootdir,
            path,
            full_path);
  }

  int
  Mos_oper::open(const char * path, fuse_file_info * file_info) noexcept
  {
    int fd;
    char full_path[PATH_MAX];

    Mos_oper::full_path(full_path, path);

    /* logs the full path, and the address of the fi pointer. */
    log_msg("Mos_oper::open(full_path = %s, file_info = 0x%08x)\n", full_path, file_info);
    fd = unix::Filesystem::Open(full_path, (file_info->flags)).unwrap();

    file_info->fh = fd;
    log_file_info(file_info);

    return fd;
  }

  int
  Mos_oper::read(const char * path,
                 char * buffer,
                 size_t size,
                 off_t offset,
                 struct fuse_file_info * file_info) noexcept
  {
    log_msg(
      "Mos_oper::read(path = %s, buffer = 0x%08x, size = %d, offset = %lld, file_info = "
      "0x%08x)\n",
      path,
      buffer,
      size,
      offset,
      file_info);

    return unix::Filesystem::Pread(file_info->fh, buffer, size, offset).unwrap();
  }

  int
  Mos_oper::readdir(const char * path,
                    void * buffer,
                    fuse_fill_dir_t filler,
                    off_t offset,
                    fuse_file_info * file_info) noexcept
  {
    DIR * dir_ptr;
    struct dirent * dir;

    log_msg("Mos_oper::readdir(path = %s, buffer = 0x%08x, filler=0x%08x, offset=%lld, "
            "file_info=0x%08x)\n",
            path,
            buffer,
            filler,
            offset,
            file_info);

    dir_ptr = reinterpret_cast<DIR *>(reinterpret_cast<uintptr_t>(file_info->fh));
    dir = unix::Filesystem::Readdir(dir_ptr).unwrap();

    /* Just copy the underlying directory's filenames into the mounted directory. */
    do
      {
        log_msg("Calling filler with name %s\n", dir->d_name);
        /* The offset 0 is passed to `filler()`.
           This tells `filler()` to manage the offsets into
           the directory structure for itself. */
        if (filler(buffer, dir->d_name, NULL, 0) != 0)
          return -ENOMEM;
    } while ((dir = unix::Filesystem::Readdir(dir_ptr).unwrap()) != NULL);

    log_file_info(file_info);

    return 0;
  }
}