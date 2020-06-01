/*
    ustar.c - contains tar initrd routines
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <kernel/kernel.h>
#include <kernel/multiboot.h>
#include <kernel/vfs.h>
#include <kernel/api.h>
#include <string.h>

char* base = 0;

vfs_filesystem filesystem;

int oct2bin(char *in)
{
  unsigned int size = 0;
  unsigned int j;
  unsigned int count = 1;

  for (j = 11; j > 0; j--, count *= 8)
      size += ((in[j - 1] - '0') * count);

  return size;
}

void initrd_umount()
{

}

void initrd_mount()
{

}

vfs_file file;

vfs_file* initrd_open(char* name, int open_flags)
{
    char* ptr = base;
    if(name[0] == '/')
        name++;
    while(!memcmp(ptr + 257, "ustar", 5))
    {
        int size = oct2bin(ptr + 0x7c);
        if(!memcmp(ptr, name, strlen(name) + 1))
        {
            strcpy(file.name, name);
            file.size = size;
            file.pos = 0;
            file.device = 'a';
            file.flags = FS_FILE;
            file.owning_tid = sys_get_tid();
            file.open_flags = open_flags;
            return (vfs_file*)&file;
        }
        ptr += (((size + 511) / 512) + 1) * 512;
    }
    return (vfs_file*)0;
}

void initrd_read(vfs_file* file, uint8_t* buffer, uint32_t num_bytes)
{
    int size = 0;
    void* temp_buffer = read_file(file->name, &size);
    if(num_bytes > size)
        memcpy(buffer, temp_buffer, size);
    memcpy(buffer, temp_buffer, num_bytes);
    file->pos += num_bytes;
    if(file->pos < file->size)
        file->pos = FS_EOF;
}

void initrd_close(vfs_file* file)
{
    kfree(file);
}

void init_initrd(uint32_t addr)
{
    base = (char*)addr;
}

void load_initrd(int size)
{
    void* buffer = (void*)kmalloc(size);
    memcpy(buffer, base, size);
    base = buffer;
    serial_write_string("[kernel] initrd initialized.\r\n");
    strcpy(filesystem.name, "initrd");
    filesystem.read_dir = 0;
    filesystem.read = initrd_read;
    filesystem.open = initrd_open;
    filesystem.close = initrd_close;
    filesystem.mount = initrd_mount;
    filesystem.umount = initrd_umount;
    vfs_mount(&filesystem, 'a');
    serial_write_string("[kernel] Root filesystem mounted\r\n");
}

void* read_file(char* name, int* size)
{
    char* ptr = base;
    while(!memcmp(ptr + 257, "ustar", 5))
    {
        int isize = oct2bin(ptr + 0x7c);
        if(!memcmp(ptr, name, strlen(name) + 1))
        {
            *size = isize;
            return ptr + 512;
        }
        ptr += (((isize + 511) / 512) + 1) * 512;
    }
    return 0;
}
