#include<commit.h>

int commit(char *file_hash, size_t file_hash_len, char *path) {
	char prev_commit_hash[HASH_BUF_LENGTH];
	char tree_hash[HASH_BUF_LENGTH];
	char commit_hash[HASH_BUF_LENGTH];
	char *p;
	int i;

	assert(file_hash_len==HASH_BUF_LENGTH);

	if(branch(prev_commit_hash,HASH_BUF_LENGTH)<0) { return -1; }

	/*
	 * add object to tree from cache using git update-index
	 * and update extra branch's ref to point at new commit:
	 * 1. git update-index --add --cacheinfo 100644 [FILE_HASH] [PATH]
	 * 2. git write-tree
	 * 3. git commit-tree -m "[COMMIT_MESSAGE]" [HASH from (2)] -p [PARENT_COMMIT_HASH]
	 * 4. git update-ref refs/heads/[EXTRA_BRANCH_NAME] [HASH from (3)]
	 */

	// 1.)
	if(git_update_index(file_hash,path)<0) { goto reset; }

	// 2.)
	if(git_write_tree(tree_hash,HASH_BUF_LENGTH)<0) { goto reset; }

	// 3.)
	if(git_commit_tree(tree_hash,prev_commit_hash,commit_hash,HASH_BUF_LENGTH)<0) { goto reset; }
	
	// 4.)
	p = prepend("refs/heads/",global_opts.branch);
	if(NULL==p) { goto reset; }
	if(git_update_ref(commit_hash,p)<0) { goto reset; }
	free(p);
	
	if(branch_reset()<0) { return -1; }
	
	return 1;
	reset:
		if(branch_reset()<0) { return -1; }
		return -1;
}