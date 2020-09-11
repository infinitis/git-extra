#include<editor.tests.h>

int main() {
	setup_env();

	editor_basic_test();

	clean_env();
}

void editor_basic_test() {
	defaults();

	assert(editor(NULL)<0);
	assert(editor("filewhichdoesntexist.txt")<0);
	
	assert(editor("test.txt")>0);

	global_opts.editor = "sh -c 'echo \"$0\"'";
	assert(editor("test.txt")<0);
}