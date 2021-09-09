#include "../includes/minishell.h"

int	check_quotes(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\"')
			str = ft_strchr(str + 1, '\"');
		if (!str)
			return (0);
		if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		if (!str)
			return (0);
		str++;
	}
	return (1);
}

void	display_prompt(void)
{
	ft_putstr_fd("minishell$ ", 2);
}

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
	return (NULL);
}

void	main_cycle(char *str, char **temp, t_list *envlist, t_ast *ast)
{
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			my_exit(NULL);
		if (ft_strlen(str) > 0)
			add_history(str);
		else
			continue ;
		if (!check_quotes(str))
		{
			printf("quote_error\n");
			rl_replace_line("", 0);
			rl_redisplay();
			continue ;
		}
		str = replace_envs(str, envlist, 0);
		str = split_to_tokens(str, &temp);
		if (temp == NULL)
			continue ;
		ast = generate_ast(temp);
		exec_ast(ast, envlist);
		free_ast(ast);
		temp = free_arr(temp);
	}
}

int	main(int argc, char const *argv[], char const *envp[])
{
	char	*str;
	char	**temp;
	t_list	*envlist;
	t_ast	*ast;

	(void) argv;
	(void)argc;
	(void)ast;
	g_excd_sig.signal = 0;
	temp = NULL;
	str = NULL;
	ast = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	envlist = converter((char **)envp);
	main_cycle(str, temp, envlist, ast);
	return (0);
}
