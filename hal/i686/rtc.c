/*
    rtc.c - contains real time clock driver
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/
#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/init.h>
#include <sys/io.h>
#include "../hal-i386.h"
#include "include/cmos.h"

#define CENTURY 2000

uint8_t second = 0;
uint8_t minute = 0;
uint8_t hour = 0;
uint8_t day_of_week = 0;
uint8_t day = 0;
uint8_t month = 0;
uint8_t year = 0;

int get_update_flag()
{
    cmos_write_reg(RTC_UPDATE_REG);
    return cmos_read() & CMOS_NMI_DISABLE;
}

uint8_t get_rtc_reg(uint8_t reg)
{
    cmos_write_reg(reg);
    return cmos_read();
}

int get_year()
{
    return year + CENTURY;
}

int get_second()
{
    return second;
}

int get_minute()
{
    return minute;
}

int get_hour()
{
    return hour;
}

int get_day_of_week()
{
    return day_of_week;
}

int get_day()
{
    return day;
}

int get_month()
{
    return month;
}

void rtc_read()
{
    uint8_t reg_b;
    while(get_update_flag());
    second = get_rtc_reg(RTC_SECS);
    minute = get_rtc_reg(RTC_MIN);
    hour = get_rtc_reg(RTC_HOUR);
    day_of_week = get_rtc_reg(RTC_WEEKDAY);
    day = get_rtc_reg(RTC_DAY);
    month = get_rtc_reg(RTC_MONTH);
    year = get_rtc_reg(RTC_YEAR);
    reg_b = get_rtc_reg(RTC_REG_B);
    if (!(reg_b & 0x04))
    {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
    }

    if (!(reg_b & 0x02) && (hour & 0x80))
    {
        hour = ((hour & 0x7F) + 12) % 24;
    }
}

void rtc_irq(regs* r)
{
    rtc_read();
    cmos_write_reg(0x0C);
    cmos_read();
}

void rtc_init()
{
    disable();
    irq_install_handler(8, rtc_irq);
    cmos_write_reg(RTC_REG_B);
    uint8_t prev = cmos_read();
    cmos_write_reg(RTC_REG_B);
    outb(CMOS_DATA_REG, prev | 0x40);
    serial_printf("[hal] RTC initialized.\r\n");
}

#endif
