#include "../includes/minishell.h"

int	change_in(t_ast *node, int *fd_redir, t_list *envlist)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_redir[1]);
		dup2(fd_redir[0], 0);
		close(fd_redir[0]);
		node->exec(node, envlist);
		exit(1);
	}
	return (pid);
}

int	change_out(t_ast *node, int *fd_redir, t_list *envlist)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_redir[0]);
		dup2(fd_redir[1], 1);
		close(fd_redir[1]);
		node->exec(node, envlist);
		exit(1);
	}
	return (pid);
}

void	pipe_exec(t_ast *self, t_list *envlist)
{
	int	fd_redir[2];
	int	left_pid;	
	int	right_pid;
	int	pipe_check;

	pipe_check = pipe(fd_redir);
	if (pipe_check == -1)
		exit(1);
	right_pid = change_out(self->right, fd_redir, envlist);
	left_pid = change_in(self->left, fd_redir, envlist);
	close(fd_redir[0]);
	close(fd_redir[1]);
	waitpid(right_pid, NULL, 0);
	waitpid(left_pid, NULL, 0);
}	
