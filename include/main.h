#ifndef __MAIN_H_

#include<getopt.h>
#include<stdlib.h>
#include<string.h>

#include<add.h>
#include<cat.h>
#include<default.h>
#include<edit.h>
#include<log.h>
#include<ls.h>
#include<opt.h>

#define MAIN_BRANCH_SET_MESSAGE "using branch `%s`\n"
#define MAIN_EDITOR_SET_MESSAGE "using %s as editor\n"
#define MAIN_UNKNOWN_SUBCOMMAND_MESSAGE "unknown command `git ex %s`\n"
#define MAIN_WRONG_NUMBER_ARGS "wrong number of arguments\n"

#define MAIN_SUBCOMMAND_ADD "add"
#define MAIN_SUBCOMMAND_CAT "cat"
#define MAIN_SUBCOMMAND_EDIT "edit"
#define MAIN_SUBCOMMAND_LS "ls"

int main(int,char**);

#endif