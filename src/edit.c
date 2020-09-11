#include<edit.h>

int edit(char *path) {
	char file_hash[HASH_BUF_LENGTH];
	fpos_t pos;
	int fd;

	if(NULL==path) { return EXIT_FAILURE; }

	char filename[] = "/tmp/XXXXXX";
	fd = mkstemp(filename);
	close(fd);

	log_message(LOG_LEVEL_VERBOSE,EDIT_MESSAGE_TEMP_FILENAME,filename);

	// redirect stdout to tmp file
	fd = dup(fileno(stdout));
	if(NULL==freopen(filename,"w",stdout)) {
		perror("freopen() failed");
		return EXIT_FAILURE;
	}

	fflush(stdout);
	
	if(cat(path)!=EXIT_SUCCESS) { return EXIT_FAILURE; }

	// reset stdout
	while((dup2(fd,fileno(stdout))==-1)&&(errno==EINTR)) {}
	close(fd);
	clearerr(stdout);
	fsetpos(stdout,&pos); /* for C9X */

	if(add_to_index(filename,path)<0) { return EXIT_FAILURE; }

	log_message(LOG_LEVEL_DEFAULT,EDIT_MESSAGE_EDITTED_FILE,path);

	return EXIT_SUCCESS;
}