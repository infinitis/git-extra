#include<git.h>

char *argv[10];

int git(enum git_exec_flags flags, char *input, char *output, size_t output_len, ...) {
	va_list args;
	va_start(args,output_len);
	int i;

	memset(argv,0,sizeof argv);

	i = 0;
	while(1) {
		argv[i] = va_arg(args,char*);
		if(NULL==argv[i]) { break; }
		i++;
	}
	va_end(args);
	
	if(flags&GIT_EXEC_FLAG_WITH_STDS) {
		return exec_cmd_with_stds(argv);
	}
	return exec_cmd(argv,input,output,output_len);
}