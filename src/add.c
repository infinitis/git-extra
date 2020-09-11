#include<add.h>

int add(char *path) {
	char ls_tree_result[LS_TREE_ENTRY_LENGTH];

	if(NULL==path) { return EXIT_FAILURE; }

	// verify not attempting to add same file again
	if(branch_exists()>0) {
		ls_tree_result[0] = 0;
		if(git_ls_tree(path,ls_tree_result,LS_TREE_ENTRY_LENGTH)<0) { return EXIT_FAILURE; }
		if(ls_tree_result[0]!=0) {
			log_message(LOG_LEVEL_ERRORS,ADD_MESSAGE_ALREADY_ADDED,path);
			return EXIT_FAILURE;
		}
	}

	char filename[] = "/tmp/XXXXXX";
	int fd = mkstemp(filename);
	if(fd<0) { return EXIT_FAILURE; }

	log_message(LOG_LEVEL_VERBOSE,ADD_MESSAGE_TEMP_FILENAME,filename);
	
	if(NULL!=global_opts.template) {
		if(template(fd)<0) {
			close(fd);
			return EXIT_FAILURE;
		}
	}

	close(fd);

	if(add_to_index(filename,path)<0) { return EXIT_FAILURE; }

	log_message(LOG_LEVEL_DEFAULT,ADD_MESSAGE_ADDED_FILE,path);

	return EXIT_SUCCESS;
}

int add_to_index(char *tmp_filename, char *path) {
	char file_hash[HASH_BUF_LENGTH];
	int i;

	if(editor(tmp_filename)<0) { goto cleanup; }

	// add tmp file to index
	if(git_hash_object(tmp_filename,HASH_OBJECT_ADD_TO_INDEX,file_hash,HASH_BUF_LENGTH)<0) { goto cleanup; }

	log_message(LOG_LEVEL_VERBOSE,ADD_MESSAGE_ADDED_FILE_INDEX_HASH,path,file_hash);

	// delete file
	if(remove(tmp_filename)!=0) { return -1; }
	
	if(NULL!=global_opts.path_prefix) {
		char *tmp = malloc(sizeof(char)*(strlen(path)+strlen(global_opts.path_prefix)+1));
		if(NULL==tmp) { return -1; }

		strcpy(tmp,global_opts.path_prefix);
		strcat(tmp,path);

		path = tmp;
	}

	if(commit(file_hash,HASH_BUF_LENGTH,path)<0) { return -1; }

	return 1;
	cleanup:
		remove(tmp_filename);
		return -1;
}