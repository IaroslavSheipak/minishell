#include "../includes/minishell.h"

void	two_right_exec(t_ast *self)
{
	int	redir_fd;

	redir_fd = open(self->left->token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (redir_fd < 0)
		exit(1);
	dup2(redir_fd, 1);
	close (redir_fd);
}

void	one_right_exec(t_ast *self)
{
	int	redir_fd;

	redir_fd = open(self->left->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (redir_fd < 0)
		exit(1);
	dup2(redir_fd, 1);
	close(redir_fd);
}

void	one_left_exec(t_ast *self)
{
	int	redir_fd;

	redir_fd = open(self->left->token, O_RDONLY, S_IRWXU);
	if (redir_fd < 0)
		exit(1);
	dup2(redir_fd, 0);
	close (redir_fd);
}

void	two_left_exec(t_ast *self, t_list *envlist)
{
	int		redir_fd;
	char	*str;

	(void)envlist;
	redir_fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (redir_fd < 0)
		exit(1);
	str = 0;
	while (1)
	{
		str = readline("");
		if (ft_strcmp(str, self->left->token) == 0)
			break ;
		str = handle_two_left(str, redir_fd, envlist);
	}
	free(str);
	close(redir_fd);
	redir_fd = open("heredoc", O_RDONLY, S_IRWXU);
	dup2(redir_fd, 0);
	close (redir_fd);
}

void	redir_exec(t_ast	*self, t_list *envlist)
{
	if (ft_strcmp(self->token, ">") == 0)
		one_right_exec(self);
	else if (ft_strcmp(self->token, "<") == 0)
		one_left_exec(self);
	else if (ft_strcmp(self->token, ">>") == 0)
		two_right_exec(self);
	else if (ft_strcmp(self->token, "<<") == 0)
		two_left_exec(self, envlist);
	if (self->right)
		self->right->exec(self->right, envlist);
}
