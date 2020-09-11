#include<prepend.h>

char *prepend(char *prefix, char *str) {
	char *p;
	int len;

	assert(prefix!=NULL);

	if(NULL==str) { return NULL; }
	
	len = strlen(str);
	len += strlen(prefix);
	
	//sanity check len - no way branch name should be this large
	if(len>100) { return NULL; }

	p = malloc(sizeof(char)*(len));
	
	strcpy(p,prefix);
	strcat(p,str);

	return p;
}