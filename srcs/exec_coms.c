#include "../includes/minishell.h"

char	**collect_args(t_ast *self)
{
	char	**res;
	t_ast	*ptr;

	res = NULL;
	arraddelem(&res, "minishell");
	ptr = self->right;
	while (ptr != NULL)
	{
		arraddelem(&res, ptr->token);
		ptr = ptr->right;
	}
	return (res);
}

int	is_builtin(t_ast *self)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(self->token);
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	i = 0;
	if (ft_strchr(self->token, '/'))
		return (0);
	if (ft_strcmp("echo", tmp) * ft_strcmp("export", tmp)
		* ft_strcmp("unset", tmp) * ft_strcmp("cd", tmp)
		* ft_strcmp("pwd", tmp) * ft_strcmp("env", tmp)
		* ft_strcmp("exit", tmp) == 0)
		i = 1;
	free(tmp);
	return (i);
}

void	handle_chldsig(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit :3\n", 2);
		g_excd_sig.excode = 131;
	}
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_excd_sig.excode = 130;
	}
}

void	get_exit_code(char *token, char **args, t_list *envlist)
{
	int	pid;
	int	status;

	pid = my_execve(token, args, envlist);
	waitpid(pid, &status, 0);
	handle_chldsig(status);
	if (g_excd_sig.excode < 130 || g_excd_sig.excode > 132)
		g_excd_sig.excode = WEXITSTATUS(status);
}

void	cmd_exec(t_ast	*self, t_list *envlist)
{
	char	**args;
	int		i;

	i = 0;
	self->token = ft_quottrim(self->token);
	args = NULL;
	args = collect_args(self);
	while (args[i] != NULL)
	{
		args[i] = ft_quottrim(args[i]);
		i++;
	}
	if (is_builtin(self))
		exec_builtin(self->token, args, envlist);
	else
		get_exit_code(self->token, args, envlist);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	free_arr(args);
}
