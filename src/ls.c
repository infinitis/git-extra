#include<ls.h>

int ls(int ls_flag) {
	log_message(LOG_LEVEL_VERBOSE,"flag: %d\n",ls_flag);
	global_opts.ls_options = (GIT_LS_TREE_OPTION_FULL==ls_flag)?GIT_LS_TREE_OPTION_FULL:GIT_LS_TREE_OPTION_NAME_ONLY;
	
	log_message(LOG_LEVEL_VERBOSE,LS_MESSAGE_TREE_LEVEL,ls_flag);

	// get list of files based on directory relative to git root
	if(git_ls_tree(NULL,NULL,0)<0) { return EXIT_FAILURE; }
	
	return EXIT_SUCCESS;
}