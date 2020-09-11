#include<branch.tests.h>

int main() {
	setup_env();

	branch_create_basic_test();
	reset_env();

	branch_exists_basic_test();
	reset_env();

	branch_basic_test();
	branch_reset_basic_test();

	clean_env();
}

void branch_basic_test() {
	global_opts.branch = "extra";

	char got[HASH_BUF_LENGTH];

	assert(1==branch(got,HASH_BUF_LENGTH));
}

void branch_create_basic_test() {
	global_opts.branch = NULL;
	assert(branch_create()<0);

	global_opts.branch = "test";
	assert(branch_create()==1);
}

void branch_exists_basic_test() {
	global_opts.branch = "master";
	assert(branch_exists()==1);

	global_opts.branch = "notarealbranch";
	assert(branch_exists()==0);
}

void branch_reset_basic_test() {
	assert(branch_reset()==1);
}