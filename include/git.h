#ifndef __GIT_H_
#define __GIT_H_

#include<stdlib.h>
#include<string.h>

#include<exec.h>
#include<log.h>
#include<opt.h>

#define HASH_BUF_LENGTH 41

#define LS_TREE_MODE_LENGTH 7
#define LS_TREE_TYPE_LENGTH 5
#define LS_TREE_PREFIX_LENGTH LS_TREE_MODE_LENGTH+LS_TREE_TYPE_LENGTH
#define LS_TREE_ENTRY_LENGTH HASH_BUF_LENGTH+LS_TREE_PREFIX_LENGTH

#define GIT_COMMIT_DEFAULT_MESSAGE "updated using git-ex"
#define GIT_COMMIT_DEFAULT_MESSAGE_LENGTH 21

#define GIT_SYMBOLIC_REF_BRANCH_NAME_TOO_LARGE "consider making branch name shorter...\n"
#define GIT_UPDATE_REF_BRANCH_NAME_TOO_LARGE "consider making branch name shorter...\n"

enum git_exec_flags {
	GIT_EXEC_FLAG_DEFAULT = 0,
	GIT_EXEC_FLAG_WITH_STDS = 1
};

enum rev_parse_type {
	REV_PARSE_BRANCH_NAME,
	REV_PARSE_HASH,
	REV_PARSE_TOP_LEVEL
};

enum hash_object_type {
	HASH_OBJECT_DEFAULT,
	HASH_OBJECT_ADD_TO_INDEX
};

#define git_branch(output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","branch","--list",global_opts.branch,NULL)
#define git_cat_file(hash) git(GIT_EXEC_FLAG_WITH_STDS,NULL,NULL,0,"git","cat-file","-p",hash,NULL)
#define git_commit_tree(tree_hash,parent_hash,output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","commit-tree","-m",(NULL!=global_opts.message)?global_opts.message:GIT_COMMIT_DEFAULT_MESSAGE,tree_hash,(NULL!=parent_hash)?"-p":NULL,parent_hash,NULL)
#define git_config(option,output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","config","--get",option,NULL)
#define git_hash_object(filename,type,output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","hash-object",filename,(HASH_OBJECT_ADD_TO_INDEX==type)?"-w":NULL,NULL)
#define git_ls_tree(path,output,len) \
	git( \
		(NULL==path)?GIT_EXEC_FLAG_WITH_STDS:GIT_EXEC_FLAG_DEFAULT, \
		NULL, \
		output, \
		len, \
		"git", \
		"ls-tree", \
		global_opts.branch, \
		(NULL==path)?"-r":path, \
		(NULL!=path)?NULL:(GIT_LS_TREE_OPTION_NAME_ONLY==global_opts.ls_options)?"--name-only":NULL, \
		NULL \
	)
#define git_mktree(output,len) git(GIT_EXEC_FLAG_DEFAULT,"\n",output,len,"git","mktree","--batch",NULL)
#define git_reset() git(GIT_EXEC_FLAG_DEFAULT,NULL,NULL,0,"git","reset",NULL)
#define git_rev_parse(type,output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","rev-parse",(REV_PARSE_TOP_LEVEL==type)?"--show-toplevel":"--verify",(REV_PARSE_TOP_LEVEL==type)?NULL:"HEAD",(REV_PARSE_BRANCH_NAME==type)?"--abbrev-ref":NULL,NULL)
#define git_symbolic_ref(branch) git(GIT_EXEC_FLAG_DEFAULT,NULL,NULL,0,"git","symbolic-ref","HEAD",branch,NULL)
#define git_update_index(file_hash,path) git(GIT_EXEC_FLAG_DEFAULT,NULL,NULL,0,"git","update-index","--add","--cacheinfo","100644",file_hash,path,NULL)
#define git_update_ref(commit_hash,branch) git(GIT_EXEC_FLAG_DEFAULT,NULL,NULL,0,"git","update-ref",branch,commit_hash,NULL)
#define git_write_tree(output,len) git(GIT_EXEC_FLAG_DEFAULT,NULL,output,len,"git","write-tree",NULL)

int git(enum git_exec_flags,char*,char*,size_t,...);

#endif