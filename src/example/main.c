#include "fib.h"
#include "greeting.h"

#include "option_parser.h"

#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_usage( struct cmd_struct* commands, const char* name )
{
	fprintf( stderr, "usage: %s <command> [<args>]\n", name );
	fprintf( stderr, "available commands:\n" );
	for( ; commands->name; commands++ ) {
		printf( " - %s\n", commands->name );
	}
}

int main( int argc, const char** argv, const char** env )
{
	int help = 0;
	struct option options[] = {{'h', "--help", &help, OPTION_FLAG}, {'\0', "", NULL, OPTION_END}};

	struct cmd_struct commands[] = {
		{"greeting", run_greeting},
		{"fibonacci", run_fib},
		{NULL, NULL},
	};

	if( !argv[0] ) {
		print_usage( commands, "example" );
		return 2;
	}
	const char* pname = argv[0];
	argv++;

	int res = parse_options( options, &argv );
	if( res || help ) {
		print_usage( commands, pname );
		return res ? 1 : 0;
	}

	if( !argv[0] ) {
		fprintf( stderr, "missing command name; run \"%s --help\" to view commands\n", pname );
		return 1;
	}

	struct cmd_struct* cmd = get_command( commands, argv[0] );
	if( !cmd ) {
		printf( "invalid command (%s); run \"%s --help\" to view commands\n", argv[0], pname );
		return 1;
	}
	argv++;

	return cmd->fn( &argv, env );
}
