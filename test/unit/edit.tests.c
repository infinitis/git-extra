#include<edit.tests.h>

int main() {
	setup_env();

	edit_basic_test();

	clean_env();
}

void edit_basic_test() {
	defaults();

	assert(EXIT_FAILURE==edit(NULL));
	assert(EXIT_FAILURE==edit("test.txt"));

	assert(EXIT_SUCCESS==add("test.txt"));
	assert(EXIT_SUCCESS==edit("test.txt"));

	assert(EXIT_FAILURE==edit("test2.txt"));
}