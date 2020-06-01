/*
    driver.c - contains driver framework implementation
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/terminal.h>
#include <kernel/init.h>
#include <kernel/driver_core.h>

typedef struct _driver
{
    int id;
    int state;
    void* state_functions[3];
    void* init_funct;
}driver;

driver* drivers;

void install_driver(int id, void* init_function)
{
    drivers[id].id = id;
    drivers[id].state = STATE_RUNNING;
    memset(drivers[id].state_functions, 0, sizeof(uint32_t) * 3);
    drivers[id].init_funct = init_function;
    void (*init)() = drivers[id].init_funct;
    init();
    set_driver_status(id, STATE_RUNNING);
}

void uninstall_driver(int id)
{
    drivers[id].id = 0;
    drivers[id].state = STATE_STOPPED;
    if(get_status_handler(id, STATE_STOPPED) != 0)
        set_driver_status(id, STATE_STOPPED);
}

void set_status_handler(int id, int status, void* funct)
{
    drivers[id].state_functions[status] = funct;
}

void* get_status_handler(int id, int status)
{
    return drivers[id].state_functions[status];
}

void set_driver_status(int id, int status)
{
    drivers[id].state = status;
    void* fnct = drivers[id].state_functions[status];
    void(*handler)() = fnct;
    handler();
}

void start_driver_framework()
{
    serial_printf("[driver] Starting system drivers.\r\n");
    drivers = (driver*)kmalloc(25 * sizeof(drivers));
    serial_printf("[driver] Starting driver %d.\r\n", DRIVER_PARALLEL);
    install_driver(DRIVER_PARALLEL, parallel_init);
    serial_printf("[driver] Starting driver %d.\r\n", DRIVER_VIDEO);
    install_driver(DRIVER_VIDEO, video_init);
    serial_printf("[driver] Starting driver %d.\r\n", DRIVER_TERMINAL);
    install_driver(DRIVER_TERMINAL, terminal_init);
    serial_printf("[driver] Starting driver %d.\r\n", DRIVER_SERIAL);
    install_driver(DRIVER_SERIAL, serial_driver_init);
}
