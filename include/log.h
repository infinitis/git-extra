#ifndef __LOG_H_
#define __LOG_H_

#include<stdarg.h>
#include<stdio.h>

extern int verbose_flag;

enum log_level {
	LOG_LEVEL_SILENT = -1, /* suppresses all output */
	LOG_LEVEL_ERRORS = 0,  /* only prints errors */
	LOG_LEVEL_DEFAULT = 1, /* normal output */
	LOG_LEVEL_VERBOSE = 2  /* logging and debugging info */
};

void log_message(enum log_level,const char*,...);

#endif