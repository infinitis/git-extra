#include<default.h>

struct options global_opts = {NULL,NULL,NULL,NULL,NULL,GIT_LS_TREE_OPTION_FULL};

int defaults() {
	default_branch();
	if(default_editor()<0) { return -1; }
	if(default_path_prefix()<0) { return -1; }

	return 1;
}

void default_branch() {
	global_opts.branch = getenv("GIT_EX_BRANCH");
	if(NULL==global_opts.branch) {
		global_opts.branch = "extra";
	}
}

int default_editor() {
	/*
	 * editor can be found in multiple places: (ordered by priority)
	 * -passed in via option (handled in main.c (called after this)
	 * -EDITOR env variable
	 * -git config
	*/
	global_opts.editor = getenv("EDITOR");
	if(NULL==global_opts.editor) {
		char tmp[100]; // should be no longer than this; copying to global_opts below

		if(git_config("core.editor",tmp,100)<0) {
			/*
			 * will error out if core.editor
			 * not set, proceed
			 */
			return 1;
		}

		int i = strlen(tmp);
		if(i>0) {
			global_opts.editor = malloc(sizeof(char)*(i+1));
			strcpy(global_opts.editor,tmp);
		}
	}

	return 1;
}

int default_path_prefix() {
	/*
	 * generate path prefix for when not working in git root directory
	 */
	char *cwd,*root;
	int i,cwd_len,root_len;

	cwd = getcwd(NULL,0);
	if(NULL==cwd) { return -1; }

	// root will be at least as long as cwd
	cwd_len = strlen(cwd)+1;
	root = malloc(sizeof(char)*cwd_len);
	if(NULL==root) { return -1; }

	if(git_rev_parse(REV_PARSE_TOP_LEVEL,root,cwd_len)<0) { return -1; }
	
	cwd_len--;
	root_len = strlen(root);

	if(root_len<cwd_len) {
		global_opts.path_prefix = malloc(sizeof(char)*(cwd_len-root_len+2));
		strcpy(global_opts.path_prefix,&(cwd[root_len]));
		strcat(global_opts.path_prefix,"/");
	}
	
	free(cwd);

	return 1;
}