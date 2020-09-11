#ifndef __BRANCH_H_
#define __BRANCH_H_

#include<assert.h>
#include<stddef.h>

#include<exec.h>
#include<git.h>
#include<log.h>
#include<opt.h>
#include<prepend.h>

#define BRANCH_MISSING_MESSAGE "branch `%s` missing\n"
#define BRANCH_CREATED_MESSAGE "branch `%s` created\n"
#define BRANCH_RESET_MESSAGE "switch back to branch `%s` \n"
#define BRANCH_WORKING_BRANCH_ERROR_MESSAGE "failed to get current working branch; additional output might be printed above\n"

int branch(char*,size_t);
int branch_create();
int branch_exists();
int branch_reset();

#endif