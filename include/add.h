#ifndef __ADD_H_
#define __ADD_H_

#include<stdio.h>
#include<stdlib.h>

#include<commit.h>
#include<editor.h>
#include<git.h>
#include<log.h>
#include<opt.h>
#include<templ.h>

#define ADD_MESSAGE_ADDED_FILE_INDEX_HASH "added %s to index with hash: %s\n"
#define ADD_MESSAGE_ALREADY_ADDED "%s already exists\n"
#define ADD_MESSAGE_ADDED_FILE "added %s\n"
#define ADD_MESSAGE_TEMP_FILENAME "temporary file %s created\n"

int add(char*);
int add_to_index(char*,char*);

#endif