#include<commit.tests.h>

int main() {
	setup_env();

	commit_basic_test();

	clean_env();
}

void commit_basic_test() {
	assert(0==system("echo 'test2' > test2.txt"));

	global_opts.branch = "extra";

	char file_hash[HASH_BUF_LENGTH];
	memset(file_hash,0,HASH_BUF_LENGTH);

	char **argv;
	int i;
	
	assert(1==git_hash_object("test2.txt",HASH_OBJECT_ADD_TO_INDEX,file_hash,HASH_BUF_LENGTH));
	
	char c = file_hash[0];
	file_hash[0]++;
	assert(commit(file_hash,HASH_BUF_LENGTH,"hahahah")<0);

	file_hash[0] = c;
	assert(1==commit(file_hash,HASH_BUF_LENGTH,"hahahah"));
}