#include "fib.h"

#include "option_parser.h"

#include <stdio.h>

int fib( int n )
{
	if( n < 2 )
		return 1;
	return fib( n - 1 ) + fib( n - 2 );
}

int run_fib( const char*** argv, const char** env )
{

	int res;
	int n = 3;
	int help = 0;

	struct option options[] = {OPT_INT( 'n', "num", &n, "fibonacci number to print" ),
							   OPT_FLAG( 'h', "help", &help, "display this help text" ),
							   OPT_END};

	res = parse_options( options, argv );
	if( res ) {
		return res;
	}
	if( help ) {
		print_help( options );
		return 0;
	}

	printf( "%d\n", fib( n ) );

	return res;
}
