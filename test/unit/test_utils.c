#include<test_utils.h>

void clean_env() {
	assert(chdir("..")==0);
	assert(0==system("rm -rf working"));
}

void reset_env() {
	clean_env();
	setup_env();
}

void setup_env() {
	// remove old test directory (if previous test failed)
	assert(0==system("rm -rf working"));
	
	assert(0==system("git init working"));
	
	assert(chdir("working")==0);
	
	assert(0==system("git config --local user.email \"test@test.com\""));
	assert(0==system("git config --local user.name \"test@test.com\""));
	assert(0==system("git config --local core.editor \"sh -c 'echo \\\"hello\\\" >> \\\"\\$0\\\"'\""));
	
	assert(0==system("echo \"template\n\n\nhahaha\" > test.template"));
	assert(0==system("echo \"test\" > test.txt"));
	assert(0==system("git add -A"));
	assert(0==system("git commit -a -m \"...\""));
}