#ifndef __OPT_H_
#define __OPT_H_

// global options
#define WORKING_BRANCH_BUF_SIZE 30

enum ls_tree_options {
	GIT_LS_TREE_OPTION_DEFAULT = 0,
	GIT_LS_TREE_OPTION_FULL = 1,
	GIT_LS_TREE_OPTION_NAME_ONLY = 2
};

struct options {
	char *branch;
	char *editor;
	char *message;
	char *path_prefix;
	char *template;
	enum ls_tree_options ls_options;
	char working_branch[WORKING_BRANCH_BUF_SIZE];
};

extern struct options global_opts;

#endif