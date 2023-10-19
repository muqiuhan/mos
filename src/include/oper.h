#ifndef MOS_OPER_H
#define MOS_OPER_H

#include <fuse/fuse.h>

/**
 * @brief File open operation
 * @param path Relative to the root of the mounted file system
 * @param file_info Used to maintain information about the file
 * @return -1 is returned and errno is set to indicate the error.
 */
int mos_open(const char * path, struct fuse_file_info * file_info);

/**
 * @brief Read data from some specified offset from the beginning of a file.
 * @return @param buffer
 */
int mos_read(const char * path,
            char * buffer,
            size_t size,
            off_t offset,
            struct fuse_file_info * file_info);

/**
 * @brief The fuse callback struct for MOS
 */
struct fuse_operations mos_oper = { .open = mos_open, .read = mos_read };

#endif /* MOS_OPER_H */