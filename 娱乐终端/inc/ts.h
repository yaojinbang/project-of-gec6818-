#ifndef _TS_H_
#define _TS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h>
#include <dirent.h>

int get_ts();
extern struct input_event touch_info;
extern int ts_x,ts_y;

#endif