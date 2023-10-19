#include "./include/oper.h"
#include "./include/log.h"
#include "./include/params.h"
#include <errno.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief  Translating the relative path  to a full path in the underlying filesystem.
 * @param full_path The return value
 * @param path The relative path
 */
static void
mos_full_path(char full_path[PATH_MAX], const char * path)
{
  strcpy(full_path, MOS_DATA->rootdir);
  strncat(full_path, path, PATH_MAX);

  log_msg("    mos_full_path: rootdir = %s, path = %s, full_path = %s\n",
          MOS_DATA->rootdir,
          path,
          full_path);
}

/**
 * @brief Looks up errno as set by the system call, logs the error, and returns -(errno)
 * @param msg Additional error messages
 * @return -(errno)
 */
static int
mos_error(const char * msg)
{
  log_msg("%s: %s", msg, strerror(errno));
  return errno;
}

int
mos_open(const char * path, struct fuse_file_info * file_info)
{
  int ret = 0;
  int fd;
  char full_path[PATH_MAX];

  mos_full_path(full_path, path);

  /* logs the full path, and the address of the fi pointer. */
  log_msg("mos_open(full_path = %s, file_info = 0x%08x)\n", full_path, (int)file_info);
  fd = open(full_path, file_info->flags);

  if (fd < 0)
    ret = mos_error("mos_open");

  file_info->fh = fd;
  log_fi(file_info);
}

int
mos_read(const char * path,
         char * buffer,
         size_t size,
         off_t offset,
         struct fuse_file_info * file_info)
{
  int ret = 0;

  log_msg("mos_read(path = %s, buffer = 0x%08x, size = %d, offset = %lld, file_info = "
          "0x%08x)\n",
          path,
          (int)buffer,
          size,
          offset,
          (int)file_info);

  ret = pread(file_info->fh, buffer, size, offset);

  if (ret < 0)
    ret = mos_error("mos_read");

  return ret;
}