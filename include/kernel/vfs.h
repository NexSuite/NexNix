/*
    vfs.h - contains Virtual Filesystem structures
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _VFS_H
#define _VFS_H

#include <stdint.h>
#include <stddef.h>

#define FS_EOF -1
#define FS_INVALID -2
#define FS_FILE 1
#define FS_DIRECTORY 2

#define MAX_DEVICES 26

typedef struct _vfs_file
{
    char name[255];
    uint32_t size;
    uint32_t pos;
    char device;
    uint32_t flags;
    int owning_tid;
    int open_flags;
}vfs_file;

typedef void (*enum_dir_ptr)(char* file_name, int size, int flags);

typedef vfs_file* (*read_dir_ptr)(enum_dir_ptr enum_dir, char* path);
typedef void (*read_file_ptr)(vfs_file* file, uint8_t* buffer, uint32_t num_bytes);
typedef vfs_file* (*open_file_ptr)(char* path, uint32_t flags);
typedef void (*close_file_ptr)(vfs_file* file);
typedef void (*mount_ptr)();
typedef void (*umount_ptr)();

typedef struct _vfs_filesystem
{
    char name[64];
    read_dir_ptr read_dir;
    read_file_ptr read;
    open_file_ptr open;
    close_file_ptr close;
    mount_ptr mount;
    umount_ptr umount;
}vfs_filesystem;

void vfs_umount(int device);
void vfs_mount(vfs_filesystem* filesystem, int device);
vfs_file* vfs_open(char* name, int open_flags);
void vfs_read(vfs_file* file, uint8_t* buffer, uint32_t num_bytes);
void vfs_close(vfs_file* file);
void vfs_read_dir(enum_dir_ptr enum_dir, char* path);

#endif
