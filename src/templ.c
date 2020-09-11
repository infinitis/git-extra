#include<templ.h>

int template(int tmp_fd) {
	/*
	 * copy template to temp file (if exists)
	 * will treat global_opts.template as a full path first,
	 * then search [ADD_TEMPLATE_PREFIX].template (see add.h)
	 */

	if(NULL==global_opts.template) { return 0; }

	FILE *fp = fopen(global_opts.template,"r");
	if(NULL==fp) {
		int len = strlen(global_opts.template);
		
		/*
		 * this is defined using autotools and
		 * can be modified with ./configure. See 
		 * templatesdir varible in top-level
		 * Makefile.am.
		 */
		char templatedir[] = TEMPLATE_DIR;
		len += strlen(templatedir);
		
		char *fullname = malloc(sizeof(char)*(len+TEMPLATE_EXTRA_LENGTH+1));
		if(NULL==fullname) { return -1; }

		strcpy(fullname,TEMPLATE_DIR);
		strcat(fullname,TEMPLATE_PREFIX);
		strcat(fullname,global_opts.template);
		strcat(fullname,TEMPLATE_SUFFIX);

		fp = fopen(fullname,"r");

		free(fullname);
	}

	if(fp==NULL) { return 0; }
	
	if(0!=fseek(fp,0,SEEK_END)) {
		perror("fseek() failed");
		return -1;
	}

	long size = ftell(fp);
	if(size<0) {
		perror("ftell() failed");
		return -1;
	}

	rewind(fp);

	size_t count = size;

	int template_fd = fileno(fp);
	off_t off = 0;
	while(count>0) {
		ssize_t sent = sendfile(tmp_fd,template_fd,&off,count);
		if(sent<0) {
			perror("sendfile() failed");
			fclose(fp);
			return -1;
		}
		count -= sent;
	}

	if(0!=fclose(fp)) {
		perror("fclose() failed");
		return -1;
	}

	return 1;
}