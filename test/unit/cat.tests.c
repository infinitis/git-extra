#include<cat.tests.h>

int main() {
	setup_env();

	cat_basic_test();

	clean_env();
}

void cat_basic_test() {
	assert(EXIT_FAILURE==cat(NULL));

	global_opts.branch = "extra";
	assert(EXIT_FAILURE==cat("test.txt"));

	global_opts.branch = "master";
	assert(EXIT_SUCCESS==cat("test.txt"));
}