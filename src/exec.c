#include<exec.h>

int exec_cmd(char **argv, char *input, char *output, size_t output_len) {
	int parent_to_child_fds[2];
	int child_to_parent_fds[2];

	if(pipe(parent_to_child_fds)==-1) {
		perror("pipe() failed");
		return -1;
	}

	if(pipe(child_to_parent_fds)==-1) {
		perror("pipe() failed");
		return -1;
	}

	pid_t pid = fork();
	if(pid==-1) {
		perror("fork() failed");
		return -1;
	} else if(pid==0) { // child
		int i = 0;
		while(argv[i]!=NULL) {
			log_message(LOG_LEVEL_VERBOSE,"%s ",argv[i]);
			i++;
		}

		while((dup2(parent_to_child_fds[0],STDIN_FILENO)==-1)&&(errno==EINTR)) {}
		while((dup2(child_to_parent_fds[1],STDOUT_FILENO)==-1)&&(errno==EINTR)) {}
		close(parent_to_child_fds[0]);
		close(parent_to_child_fds[1]);
		close(child_to_parent_fds[0]);
		close(child_to_parent_fds[1]);

		execvp(argv[0],argv);
		perror("execvp() failed");
		exit(1);
	}
	
	close(child_to_parent_fds[1]);

	if(NULL!=input) {
		while(1) {
			ssize_t count = write(parent_to_child_fds[1],input,strlen(input)+1);
			if(-1==count) {
				if(EINTR==errno) {
					// allow for retry if interrupted
					continue;
				} else {
					perror("read() failed");
					return -1;
				}
			}
			break;
		}
	}

	close(parent_to_child_fds[0]);
	close(parent_to_child_fds[1]);

	int status = 0;
	if(wait(&status)==-1) {
		perror("wait() failed");
		return -1;
	}

	if(status!=0) {
		log_message(LOG_LEVEL_VERBOSE,EXEC_INVALID_RETURN_STATUS,argv[0],status);
		return -1;
	}

	if(NULL!=output) {
		while(1) {
			ssize_t count = read(child_to_parent_fds[0],output,output_len);
			if(-1==count) {
				if(EINTR==errno) {
					// allow for retry if interrupted
					continue;
				} else {
					perror("read() failed");
					return -1;
				}
			}
			break;
		}

		// remove final newline from output (if exists)
		strtok(output,"\n");
		// make sure that output ends w/ '\0'
		output[output_len-1] = '\0';
	}

	close(child_to_parent_fds[0]);
	
	return 1;
}

int exec_cmd_with_stds(char **argv) {
	pid_t pid = fork();
	if(pid==-1) {
		perror("fork() failed");
		return -1;
	} else if(pid==0) { // child
		execvp(argv[0],argv);
		perror("execvp() failed");
		exit(1);
	}

	int status = 0;
	if(wait(&status)==-1) {
		perror("wait() failed");
		return -1;
	}

	if(status!=0) {
		log_message(LOG_LEVEL_VERBOSE,EXEC_INVALID_RETURN_STATUS,argv[0],status);
		return -1;
	}

	return 1;
}