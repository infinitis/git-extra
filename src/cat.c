#include<cat.h>

int cat(char *path) {
	char ls_tree_result[LS_TREE_ENTRY_LENGTH];
	
	if(NULL==path) { return EXIT_FAILURE; }

	// get reference to path in branch
	if(git_ls_tree(path,ls_tree_result,LS_TREE_ENTRY_LENGTH)<0) { return EXIT_FAILURE; }
	
	if(git_cat_file(&(ls_tree_result[LS_TREE_PREFIX_LENGTH]))<0) { return EXIT_FAILURE; }
	
	return EXIT_SUCCESS;
}