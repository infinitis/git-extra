#include<main.h>

int verbose_flag;

static struct option long_options[] = {
	{"verbose", no_argument, &verbose_flag, 1},
	{"quiet", no_argument, &verbose_flag, 0},
	{0,0,0,0}
};

int main(int argc, char **argv) {
	int c;

	while(1) {
		int option_index = 0;

		if((c = getopt_long(argc,argv,"vq",long_options,&option_index))==-1) { break; }

		switch(c) {
			case 0:
				if(long_options[option_index].flag!=0) { break; }

				printf("option %s",long_options[option_index].name);
				if(optarg) {
					printf(" with arg %s",optarg);
				}
				printf("\n");
				
				break;
			case '?':
				break;
			default:
				return EXIT_FAILURE;
		}
	}

	printf("verbose flag set\n");

	return EXIT_SUCCESS;
}