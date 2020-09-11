#include<default.tests.h>

int main() {
	setup_env();

	default_basic_test();
	default_editor_basic_test();

	clean_env();
}

void default_basic_test() {
	defaults();

	assert(0==strcmp(global_opts.branch,"extra"));
	assert(0==strcmp(global_opts.editor,"sh -c 'echo \"hello\" >> \"$0\"'"));
	assert(NULL==global_opts.path_prefix);
}

void default_editor_basic_test() {
	assert(0==setenv("EDITOR","hahahahah",1));

	assert(default_editor()==1);

	assert(0==strcmp(global_opts.editor,"hahahahah"));
}