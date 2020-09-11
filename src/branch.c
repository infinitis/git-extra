#include<branch.h>

int branch(char *commit_hash, size_t commit_hash_len) {
	char *p;
	int i;

	assert(commit_hash_len==HASH_BUF_LENGTH);

	if((i = branch_exists())<=0) {
		log_message(LOG_LEVEL_VERBOSE,BRANCH_MISSING_MESSAGE,global_opts.branch);
		if(i<0) { return -1; }
		if(branch_create()<0) { return -1; }
	}

	// store current branch into global_opts.working_branch
	if(git_rev_parse(REV_PARSE_BRANCH_NAME,global_opts.working_branch,WORKING_BRANCH_BUF_SIZE)<0) {
		log_message(LOG_LEVEL_ERRORS,BRANCH_WORKING_BRANCH_ERROR_MESSAGE);
		return -1;
	}

	// git rev-parse returns branch with \n at the end
	while(i++<WORKING_BRANCH_BUF_SIZE) {
		if(global_opts.working_branch[i]=='\0') { break; }
		if(global_opts.working_branch[i]=='\n') {
			global_opts.working_branch[i] = '\0';
			break;
		}
	}

	/* switch to extra branch and reset index
	 * 1. git symbolic-ref HEAD refs/heads/[BRANCH_NAME]
	 * 2. git reset
	 */

	p = prepend("refs/heads/",global_opts.branch); // see git.c:365
	if(NULL==p) { return -1; }
	if(git_symbolic_ref(p)<0) { return -1; }
	free(p);

	if(git_reset()<0) { return -1; }

	// store current commit's hash in buf
	if(git_rev_parse(REV_PARSE_HASH,commit_hash,HASH_BUF_LENGTH)<0) {
		log_message(LOG_LEVEL_ERRORS,BRANCH_WORKING_BRANCH_ERROR_MESSAGE);
		return -1;
	}

	return 1;
}

int branch_create() {
	char tree_hash[HASH_BUF_LENGTH];
	char commit_hash[HASH_BUF_LENGTH];
	char *p;
	
	/* 
	 * create blank branch if global_opts.branch doesn't exist:
	 * 1. echo "" | git mktree --batch
	 * 2. git commit-tree -m "init" [HASH from (1)]
	 * 3. git update-ref refs/heads/[global_opts.branch] [HASH from (2)]
	 */

	// 1.)
	if(git_mktree(tree_hash,HASH_BUF_LENGTH)<0) { return -1; }

	// 2.)
	char init_message[] = "init";
	p = global_opts.message;
	global_opts.message = init_message;
	if(git_commit_tree(tree_hash,NULL,commit_hash,HASH_BUF_LENGTH)<0) { return -1; }
	global_opts.message = p;
		
	// 3.)
	p = prepend("refs/heads/",global_opts.branch);
	if(NULL==p) { return -1; }
	if(git_update_ref(commit_hash,p)<0) { return -1; }
	free(p);

	log_message(LOG_LEVEL_VERBOSE,BRANCH_CREATED_MESSAGE,global_opts.branch);

	return 1;
}

int branch_exists() {
	char output[HASH_BUF_LENGTH];
	int i;
	
	output[0] = 0;
	if(git_branch(output,HASH_BUF_LENGTH)<0) { return -1; }
	
	if(output[0]!=0) {
		return 1;
	}
	return 0;
}

int branch_reset() {
	char *p;

	log_message(LOG_LEVEL_VERBOSE,BRANCH_RESET_MESSAGE,global_opts.working_branch);

	/* switch back to working branch and reset index
	 * 1. git symbolic-ref HEAD refs/heads/[WORKING_BRANCH_NAME]
	 * 2. git reset
	 */

	p = prepend("refs/heads/",global_opts.working_branch);
	if(NULL==p) { return -1; }
	if(git_symbolic_ref(p)<0) { return -1; }
	free(p);

	if(git_reset()<0) { return -1; }

	return 1;
}