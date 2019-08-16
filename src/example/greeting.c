#include "greeting.h"

#include "option_parser.h"

#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int run_greeting( const char*** argv, const char** env )
{

	int res;

	int num_loop = 3;
	int help = 0;
	char* greeting = "hello";
	const char* greeting_choices[] = {"hello", "bonjour", "hola", "ciao"};

	struct option options[] = {
		OPT_INT( 'n', "numloop", &num_loop, "number of times to print message" ),
		OPT_STR_CHOICES( 'g', "greeting", &greeting, "greeting to print", 4, greeting_choices ),
		OPT_FLAG( 'h', "help", &help, "display this help text" ),
		OPT_END,
	};

	res = parse_options( options, argv );
	if( res ) {
		return res;
	}
	if( help ) {
		print_help( options );
		return 0;
	}

	for( int i = 0; i < num_loop; i++ ) {
		printf( "%s\n", greeting );
	}

	return res;
}
