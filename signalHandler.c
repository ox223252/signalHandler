////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2017
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU General Public License published by the Free
///     Software Foundation, either version 2 of the License, or (at your
///     option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU General Public License for more
///     details.
///
/// You should have received a copy of the GNU General Public License along with
///     this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>

#include "signalHandler.h"

// SIGKILL : kill -9
// SIGTERM : kill
// SIGINT : Ctrl+C
// SIGQUIT : Ctrl+\   core dump
// SIGSTOP : pause process
// SIGCONT : resume process
// SIGHUP : Ctrl+D	poke process
// SIGALRM :

static signalHandling *lg_ptr;
static sigset_t g_sigsetSaved;

static void catchSignals(int sig)
{
	switch (sig)
	{
		case SIGINT:
		{
			if ( lg_ptr && lg_ptr->Int.func )
			{
				lg_ptr->Int.func ( lg_ptr->Int.arg );
			}
			break;
		}
		case SIGTERM:
		{
			if ( lg_ptr && lg_ptr->Term.func )
			{
				lg_ptr->Term.func ( lg_ptr->Term.arg );
			}
			break;
		}
		case SIGHUP:
		{
			if ( lg_ptr && lg_ptr->Hup.func )
			{
				lg_ptr->Hup.func ( lg_ptr->Hup.arg );
			}
			break;
		}
		case SIGQUIT:
		{
			if ( lg_ptr && lg_ptr->Quit.func )
			{
				lg_ptr->Quit.func ( lg_ptr->Quit.arg );
			}
			break;
		}
		case SIGSTOP:
		{
			if ( lg_ptr && lg_ptr->Stop.func )
			{
				lg_ptr->Stop.func ( lg_ptr->Stop.arg );
			}
			break;
		}
		case SIGCONT:
		{
			if ( lg_ptr && lg_ptr->Cont.func )
			{
				lg_ptr->Cont.func ( lg_ptr->Cont.arg );
			}
			break;
		}
		case SIGUSR1:
		{
			if ( lg_ptr && lg_ptr->Usr1.func )
			{
				lg_ptr->Usr1.func ( lg_ptr->Usr1.arg );
			}
			break;
		}
		case SIGUSR2:
		{
			if ( lg_ptr && lg_ptr->Usr2.func )
			{
				lg_ptr->Usr2.func ( lg_ptr->Usr2.arg );
			}
			break;
		}
		case SIGALRM:
		{
			if ( lg_ptr && lg_ptr->Alrm.func )
			{
				lg_ptr->Alrm.func ( lg_ptr->Alrm.arg );
			}
			break;
		}
		case SIGSEGV:
		{
			if ( lg_ptr && lg_ptr->Fault.func )
			{
				lg_ptr->Fault.func ( lg_ptr->Fault.arg );
			}
			break;
		}
		default:
		{
			// TODO: should all other signals be catched, and handled as SIGINT?
			//
			// Reason: currently, all other signals are just uncatched, and the OS kills us.
			// The difference is that we could then close the open files properly.
			break;
		}
	}
}

void signalHandlerInit ( signalHandling *ptr )
{
	if ( !ptr )
	{
		return;
	}

	lg_ptr = ptr;
	if ( ptr->flag.Int )
	{
		signal ( SIGINT, catchSignals );
	}
	if ( ptr->flag.Term )
	{
		signal ( SIGTERM, catchSignals );
	}
	if ( ptr->flag.Hup )
	{
		signal ( SIGHUP, catchSignals );
	}
	if ( ptr->flag.Quit )
	{
		signal ( SIGQUIT, catchSignals );
	}
	if ( ptr->flag.Stop )
	{
		signal ( SIGSTOP, catchSignals );
	}
	if ( ptr->flag.Cont )
	{
		signal ( SIGCONT, catchSignals );
	}
	if ( ptr->flag.Usr2 )
	{
		signal ( SIGUSR2, catchSignals );
	}
	if ( ptr->flag.Usr2 )
	{
		signal ( SIGUSR2, catchSignals );
	}
	if ( ptr->flag.Alrm )
	{
		signal ( SIGALRM, catchSignals );
	}
	if ( ptr->flag.Fault )
	{
		signal ( SIGSEGV, catchSignals );
	}
}

int signalHandlerSave ( sigset_t * ptr )
{
	if ( ptr != NULL )
	{
		return ( sigprocmask ( SIG_SETMASK, NULL, ptr ) );
	}
	else
	{
		return ( sigprocmask ( SIG_SETMASK, NULL, &g_sigsetSaved ) );
	}
}

int signalHandlerRestore ( sigset_t * ptr )
{
	if ( ptr != NULL )
	{
		return ( sigprocmask ( SIG_SETMASK, ptr, NULL ) );
	}
	else
	{
		return ( sigprocmask ( SIG_SETMASK, &g_sigsetSaved, NULL ) );
	}
}

int signalHandlerBlock ( int signal )
{
	sigset_t set;
	if ( sigaddset ( &set, signal ) )
	{
		return ( -1 );
	}

	return ( sigprocmask ( SIG_BLOCK, &set, NULL ) );
}

int signalHandlerUnBlock ( int signal )
{
	sigset_t set;
	if ( sigaddset ( &set, signal ) )
	{
		return ( -1 );
	}

	return ( sigprocmask ( SIG_UNBLOCK, &set, NULL ) );
}
