#ifndef __SIGNALHANDLER_H__
#define __SIGNALHANDLER_H__

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>

// SIGKILL : kill -9
// SIGTERM : kill
// SIGINT : Ctrl+C
// SIGQUIT : Ctrl+\   core dump
// SIGSTOP : pause process
// SIGCONT : resume process
// SIGHUP : Ctrl+D	poke process
// SIGALRM :

typedef struct
{
	uint8_t Int:1,
		Term:1,
		Hup:1,
		Quit:1,
		Stop:1,
		Cont:1,
		Usr1:1,
		Usr2:1,
		Alrm:1;
}
signalFlag;

typedef struct
{
	void (*func)( void * );
	void * arg;
}
signalArgs;

typedef struct
{
	signalFlag flag;
	signalArgs Int;
	signalArgs Term;
	signalArgs Hup;
	signalArgs Quit;
	signalArgs Stop;
	signalArgs Cont;
	signalArgs Usr1;
	signalArgs Usr2;
	signalArgs Alrm;
}
signalHandling;

////////////////////////////////////////////////////////////////////////////////
/// \fn void signalHandlerInit ( signalHandling *ptr );
/// \param [ in ] ptr: struct to init signal manager
/// \biref
////////////////////////////////////////////////////////////////////////////////
void signalHandlerInit ( signalHandling *ptr );

////////////////////////////////////////////////////////////////////////////////
/// \fn int signalHandlerSave ( sigset_t * ptr );
/// \param [ out ] ptr: used to store the actual context of signal manager
/// \biref this function will save the actual context of signal manger in ptr, 
///     if ptr is NULL, it will save in internal var.
/// \return if 0 then OK else see errno for more details
////////////////////////////////////////////////////////////////////////////////
int signalHandlerSave ( sigset_t * ptr );

////////////////////////////////////////////////////////////////////////////////
/// \fn int signalHandlerRestore ( sigset_t * ptr );
/// \param [ in ] ptr: used to store and old context of signal manager
/// \biref this function will restored an old context, if ptr is NULL, it will 
///     restore form internal var, signalHandlerSave() with NULL param should be
///     called earlier.
/// \return if 0 then OK else see errno for more details
////////////////////////////////////////////////////////////////////////////////
int signalHandlerRestore ( sigset_t * ptr );

////////////////////////////////////////////////////////////////////////////////
/// \fn int signalHandlerBlock ( int signal );
/// \param [ in ] signal: signal ID need to be Blocked
/// \biref this function will block signal propagation.
/// \return if 0 then OK else see errno for more details
////////////////////////////////////////////////////////////////////////////////
int signalHandlerBlock ( int signal );

////////////////////////////////////////////////////////////////////////////////
/// \fn int signalHandlerUnBlock ( int signal );
/// \param [ in ] signal: signal ID should be unblocked
/// \biref this function will unblock signal propagation.
/// \return if 0 then OK else see errno for more details
////////////////////////////////////////////////////////////////////////////////
int signalHandlerUnBlock ( int signal );

#endif