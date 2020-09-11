#include<hash.tests.h>

int main() {
	setup_env();

	hash_basic_test();

	clean_env();
}

void hash_basic_test() {
	char expected[HASH_BUF_LENGTH] = "9daeafb9864cf43055ae93beb0afd6c7d144bfa4";
	char got[HASH_BUF_LENGTH];

	memset(got,0,HASH_BUF_LENGTH);

	assert(hash("test.txt",got,HASH_BUF_LENGTH)==1);

	assert(memcmp(expected,got,HASH_BUF_LENGTH)==0);
}