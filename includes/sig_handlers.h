#ifndef SIG_HANDLERS_H
# define SIG_HANDLERS_H
# include "minishell.h"

void	proc_signal_handler(int signum);
void	signal_handler(int signo);
void	handle_sigquit(void);
void	handle_sigint(int sig);
#endif
