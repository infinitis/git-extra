#ifndef __TEMPL_H_
#define __TEMPL_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/sendfile.h>

#include<opt.h>

#define TEMPLATE_PREFIX "/"
#define TEMPLATE_PREFIX_LENGTH 1
#define TEMPLATE_SUFFIX ".template"
#define TEMPLATE_SUFFIX_LENGTH 9
#define TEMPLATE_EXTRA_LENGTH TEMPLATE_PREFIX_LENGTH+TEMPLATE_SUFFIX_LENGTH

int template(int);

#endif