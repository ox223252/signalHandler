# signalHandler:

Use it to manage signals, to set what default function call on signal event, block or unblock signals.

## Example:
```C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "signalHandler/signalHandler.h"

void functionExit ( void * arg )
{
	static int i = 1;

	printf ( " | %d | %s", i, ( char * )arg );

	if ( i++ >= 5 )
	{
		exit ( 0 );
	}
}

void main ( void )
{
	signalHandling signal =
	{
		.flag =
		{
			.Int = 1,
			.Quit = 1,
			.Term = 1
		},
		.Int =
		{
			.func = functionExit,
			.arg = "Int case\n"
		},
		.Quit =
		{
			.func = functionExit,
			.arg = "Quit case\n"
		},
		.Term =
		{
			.func = functionExit,
			.arg = "Term case\n"
		}
	};

	printf ( "pid: %d\n", getpid ( ) );
	signalHandlerInit ( &signal );

	signalHandlerSave ( NULL );

	printf ( "block \"Ctrl + C\"\n");
	signalHandlerBlock ( SIGINT );
	sleep ( 10 );
	printf ( "\nblock \"Ctrl + '\"(4)\n");
	signalHandlerBlock ( SIGQUIT );
	sleep ( 10 );
	printf ( "\nunblock \"Ctrl + '\"(4)\n");
	signalHandlerUnBlock ( SIGQUIT );
	
	printf ( "\nunblock all\n" );
	signalHandlerRestore ( NULL );



	while ( 1 )
	{
		sleep ( 1 );
	}
}
```

## Result:
```Shell
> gcc main.c signalHandler/signalHandler.c && ./a.out
pid: 4346
block "Ctrl + C"
^C^C^C^\ | 1 | Quit case

block "Ctrl + '"(4)
^\^\^\
unblock "Ctrl + '"(4)
 | 2 | Quit case

unblock all
 | 3 | Int case
^C | 4 | Int case
 | 5 | Term case
```

```Shell 
> kill 4346
```