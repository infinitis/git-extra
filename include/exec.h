#ifndef __EXEC_H_
#define __EXEC_H_

#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#include<log.h>

#define EXEC_INVALID_RETURN_STATUS "%s invalid return status [%d]\n"

int exec_cmd(char**,char*,char*,size_t);
int exec_cmd_with_stds(char**);

#endif