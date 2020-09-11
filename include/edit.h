#ifndef __EDIT_H_
#define __EDIT_H_

#include<stdio.h>
#include<stdlib.h>

#include<add.h>
#include<cat.h>
#include<commit.h>
#include<log.h>

#define EDIT_MESSAGE_EDITTED_FILE "%s saved\n"
#define EDIT_MESSAGE_TEMP_FILENAME "temporary file %s created\n"

int edit(char*);

#endif