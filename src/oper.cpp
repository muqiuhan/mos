#include "./include/oper.h"
#include "./include/log.h"
#include "./include/params.h"
#include "./include/unix.h"
#include <errno.h>
#include <linux/limits.h>
#include <string.h>
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
  Mos_oper::open(const char * path, fuse_file_info * file_info) noexcept
  {
    int ret = 0;
    int fd;
    char full_path[PATH_MAX];

    Mos_oper::full_path(full_path, path);

    /* logs the full path, and the address of the fi pointer. */
    log_msg("Mos_oper::open(full_path = %s, file_info = 0x%08x)\n", full_path, file_info);
    fd = unix::Filesystem::Open(full_path, (file_info->flags)).unwrap();

    if (fd < 0)
      ret = mos_error("Mos_oper::open");

    file_info->fh = fd;
    log_fi(file_info);
  }

  int
  Mos_oper::read(const char * path,
                 char * buffer,
                 size_t size,
                 off_t offset,
                 struct fuse_file_info * file_info) noexcept
  {
    int ret = 0;

    log_msg(
      "Mos_oper::read(path = %s, buffer = 0x%08x, size = %d, offset = %lld, file_info = "
      "0x%08x)\n",
      path,
      buffer,
      size,
      offset,
      file_info);

    ret = pread(file_info->fh, buffer, size, offset);

    if (ret < 0)
      ret = mos_error("Mos_oper::read");

    return ret;
  }
}