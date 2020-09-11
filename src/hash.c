#include<hash.h>

int hash(char *filename, char *buf, int buf_len) {
	assert(buf_len==HASH_BUF_LENGTH);

	if(git_hash_object(filename,HASH_OBJECT_DEFAULT,buf,HASH_BUF_LENGTH)<0) { return -1; }

	return 1;
}