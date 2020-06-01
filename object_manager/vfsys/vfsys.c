/*
    vfs.h - contains Virtual Filesystem
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/vfs.h>
#include <kernel/api.h>

vfs_filesystem* devices[MAX_DEVICES];

void vfs_mount(vfs_filesystem* filesystem, int device)
{
    if((device - 'a') > MAX_DEVICES)
        return;
    if(filesystem)
        if(device)
            devices[device - 'a'] = filesystem;
    if(filesystem->mount)
        filesystem->mount();
}

char folder_to_letter(char* full_path, int* path_size)
{
    full_path++;
    char* folder = kmalloc(64);
    int i = 0;
    while(*full_path != '/')
    {
        folder[i] = *full_path;
        i++;
        full_path++;
    }
    *path_size = strlen(folder);
    for(int i = 0; i < MAX_DEVICES; i++)
    {
        if(strcmp(devices[i]->name, folder) == 0)
        {
            kfree(folder);
            return i + 'a';
        }
    }
    kfree(folder);
    return -1;
}

void vfs_umount(int device)
{
    if((device - 'a') > MAX_DEVICES)
        return;
    if(device)
    {
        devices[device]->umount();
        devices[device] = 0;
    }
}

vfs_file* vfs_open(char* name, int open_flags)
{
    if(name)
    {
        char* file = name;
        char device = 0;
        if(file[0] != '/' && file[1] != ':')
        {
            char* working_dir = get_working_directory(sys_get_tid());
            strcat(working_dir, file);
            strcpy(file, working_dir);
        }
        int path_size = 0;
        if(file[1] == ':')
        {
            device = file[0];
            file += 2;
        }
        else if(file[0] == '/')
        {
            device = folder_to_letter(file, &path_size);
            if(device == -1)
                return (vfs_file*)0;
            file += (path_size + 1);
        }
        return devices[device - 'a']->open(file, open_flags);
    }
    return (vfs_file*)0;
}

void vfs_read(vfs_file* file, uint8_t* buffer, uint32_t num_bytes)
{
    int device = (int)file->device - 'a';
    devices[device]->read(file, buffer, num_bytes);
}

void vfs_close(vfs_file* file)
{
    int device = (int)file->device - 'a';
    devices[device]->close(file);
}

void vfs_read_dir(enum_dir_ptr enum_dir, char* path)
{
    if(path)
    {
        char* file = path;
        char device = 'a';
        int path_size = 0;
        if(file[1] == ':')
        {
            device = file[0];
            file += 2;
        }
        else if(file[0] == '/')
        {
            device = folder_to_letter(path, &path_size);
            if(device == -1)
                return;
            file += (path_size + 1);
        }
        devices[device - 'a']->read_dir(enum_dir, path);
    }
}
