#ifndef __EDITOR_H_
#define __EDITOR_H_

#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<wordexp.h>

#include<exec.h>
#include<hash.h>
#include<log.h>
#include<opt.h>

#define EDITOR_MESSAGE_MISSING_EDITOR "no editor or core.editor config option set; set EDITOR env variable or pass --editor option\n"
#define EDITOR_MESSAGE_NO_CHANGE "no change detected; aborting...\n"

int editor(char*);

#endif