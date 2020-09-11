#include<log.h>

int verbose_flag = LOG_LEVEL_DEFAULT;

void log_message(enum log_level level, const char *format,...) {
	if(verbose_flag>=0) {
		if(level<=verbose_flag) {
			va_list args;
			va_start(args,format);
			vprintf(format,args);
			va_end(args);
		}
	}
}