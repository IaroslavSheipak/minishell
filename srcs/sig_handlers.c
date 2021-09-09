#include "../includes/minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_excd_sig.signal = 1;
	}
}

void	proc_signal_handler(int signum)
{
	(void)signum;
	exit(1);
	ft_putstr_fd("\nQuit\n", 2);
	exit(1);
}

void	handle_sigquit(void)
{
	ft_putstr_fd("Quit\n", 2);
	exit(131);
}
