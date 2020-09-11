#include<editor.h>

int editor(char *filename) {
	char pre_edit_hash[HASH_BUF_LENGTH];
	char post_edit_hash[HASH_BUF_LENGTH];

	if(NULL==filename) { return -1; }

	if(NULL==global_opts.editor) {
		log_message(LOG_LEVEL_ERRORS,EDITOR_MESSAGE_MISSING_EDITOR);
		return -1;
	}

	if(hash(filename,pre_edit_hash,HASH_BUF_LENGTH)<0) { return -1; }

	wordexp_t result;

	if(wordexp(global_opts.editor,&result,WRDE_NOCMD)!=0) { goto clean; }
	if(wordexp(filename,&result,WRDE_APPEND)!=0) { goto clean; }
	if(exec_cmd_with_stds(result.we_wordv)<0) { goto clean; }

	wordfree(&result);

	if(hash(filename,post_edit_hash,HASH_BUF_LENGTH)<0) { return -1; }

	if(memcmp(pre_edit_hash,post_edit_hash,HASH_BUF_LENGTH)==0) {
		log_message(LOG_LEVEL_DEFAULT,EDITOR_MESSAGE_NO_CHANGE);
		return -1;
	}

	return 1;
	clean:
		wordfree(&result);
		return -1;
}