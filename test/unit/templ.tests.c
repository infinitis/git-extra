#include<templ.tests.h>

int main() {
	setup_env();

	template_basic_test();

	clean_env();
}

void template_basic_test() {
	char filename[] = "/tmp/XXXXXX";
	int fd = mkstemp(filename);

	assert(fd>=0);

	global_opts.template = NULL;
	assert(template(fd)==0);

	global_opts.template = "notavalidtemplatename";
	assert(template(fd)==0);

	global_opts.template = "test.template";
	assert(template(fd)==1);
}