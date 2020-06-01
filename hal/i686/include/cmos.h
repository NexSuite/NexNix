/*
    cmos.h - contains CMOS functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _CMOS_H
#define _CMOS_H

#define CMOS_CMD_REG 0x70
#define CMOS_DATA_REG 0x71
#define CMOS_FLOPPY_REG 0x10
#define CMOS_NMI_DISABLE 0x80

#define RTC_UPDATE_REG 0x0A
#define RTC_REG_B 0x0B
#define RTC_SECS 0x00
#define RTC_MIN 0x02
#define RTC_HOUR 0x04
#define RTC_WEEKDAY 0x06
#define RTC_DAY 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09
#define RTC_CENTURY 0x32

void cmos_write_reg(int reg);
uint8_t cmos_read();

#endif
