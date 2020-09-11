#include<add.tests.h>

int main() {
	setup_env();

	add_basic_test();

	clean_env();
}

void add_basic_test() {
	defaults();
	
	assert(EXIT_FAILURE==add(NULL));
	assert(EXIT_SUCCESS==add("test.txt"));
	assert(EXIT_FAILURE==add("test.txt"));
	assert(EXIT_SUCCESS==add("test2.txt"));
}