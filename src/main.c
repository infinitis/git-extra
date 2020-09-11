#include<main.h>

/*
 * main sets the following flags
 * int verbose_flag (defined in log.c)
 */

int ls_flag = GIT_LS_TREE_OPTION_DEFAULT;

static struct option long_options[] = {
	{"long", no_argument, &ls_flag, GIT_LS_TREE_OPTION_FULL},
	{"verbose", no_argument, &verbose_flag, LOG_LEVEL_VERBOSE},
	{"quiet", no_argument, &verbose_flag, LOG_LEVEL_SILENT},
	{"branch", required_argument, 0, 'b'},
	{"editor", required_argument, 0, 'e'},
	{"message", required_argument, 0, 'm'},
	{"template", required_argument, 0, 't'},
	{0,0,0,0}
};

int main(int argc, char **argv) {
	if(defaults()<0) { return EXIT_FAILURE; }

	int c;

	while(1) {
		int option_index = 0;

		if((c = getopt_long(argc,argv,"vqm:b:e:lt:",long_options,&option_index))==-1) { break; }

		switch(c) {
			case 0:
				if(long_options[option_index].flag!=0) { break; }

				log_message(LOG_LEVEL_VERBOSE,"option %s",long_options[option_index].name);
				if(optarg) {
					log_message(LOG_LEVEL_VERBOSE," with arg %s",optarg);
				}
				log_message(LOG_LEVEL_VERBOSE,"\n");
				return EXIT_FAILURE;
				
				break;
			case 'b':
				global_opts.branch = optarg;
				break;
			case 'e':
				if(NULL!=global_opts.editor) {
					free(global_opts.editor);
				}
				global_opts.editor = optarg;
				break;
			case 'l':
				ls_flag = GIT_LS_TREE_OPTION_FULL;
				break;
			case 'm':
				global_opts.message = optarg;
				break;
			case 'q':
				verbose_flag = LOG_LEVEL_ERRORS;
				break;
			case 't':
				global_opts.template = optarg;
				break;
			case 'v':
				verbose_flag = LOG_LEVEL_VERBOSE;
				break;
			case '?':
			default:
				return EXIT_FAILURE;
		}
	}

	log_message(LOG_LEVEL_VERBOSE,MAIN_BRANCH_SET_MESSAGE,global_opts.branch);
	log_message(LOG_LEVEL_VERBOSE,MAIN_EDITOR_SET_MESSAGE,global_opts.editor);

	if(optind<argc) {
		char *p = argv[optind];
		if(strcmp(MAIN_SUBCOMMAND_ADD,p)==0) {
			if(optind+2==argc) { // 1 extra arg: path
				return add(argv[optind+1]);
			}
		} else if(strcmp(MAIN_SUBCOMMAND_CAT,p)==0) {
			if(optind+2==argc) { // 1 extra arg: path
				return cat(argv[optind+1]);
			}
		} else if(strcmp(MAIN_SUBCOMMAND_EDIT,p)==0) {
			if(optind+2==argc) { // 1 extra arg: path
				return edit(argv[optind+1]);
			}
		} else if(strcmp(MAIN_SUBCOMMAND_LS,p)==0) {
			if(optind+1==argc) {
				return ls(ls_flag);
			}
		} else {
			log_message(LOG_LEVEL_ERRORS,MAIN_UNKNOWN_SUBCOMMAND_MESSAGE,p);
			return EXIT_FAILURE;
		}
	} else {
		return ls(ls_flag);
	}

	log_message(LOG_LEVEL_ERRORS,MAIN_WRONG_NUMBER_ARGS);
	return EXIT_FAILURE;
}