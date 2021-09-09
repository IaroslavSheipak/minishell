#include "../includes/minishell.h"

char	*lex_error(char *str)
{
	ft_putstr_fd(str, 2);
	return ("\0");
}

char	*skp_onl_dlr(char *input)
{
	char	*ptr;

	ptr = ft_strchr(input, '$');
	if (ptr)
		while (ft_strchr("> <\'\"|\0", *(ptr + 1)) && ptr != NULL)
			ptr = ft_strchr(ptr + 1, '$');
	return (ptr);
}

char	*insert_env(char *input, char *before, char *env_val, char *after)
{
	char	*first_part;
	char	*res;

	first_part = ft_strjoin(before, env_val);
	res = ft_strjoin(first_part, after);
	free(before);
	free(input);
	free(first_part);
	return (res);
}

char	*env_val_name(char *input, char *ptr, char *after_env, t_list *envlist)
{
	char	*env_val;
	char	*env_name;

	if (after_env - ptr != 1)
	{	
		env_name = ft_substr(input, (ptr - input + 1), after_env - ptr - 1);
		env_val = get_env_val(env_name, envlist);
		free(env_name);
	}
	else
		env_val = ft_strdup("$");
	return (env_val);
}

char	*get_after_env(char *ptr)
{
	char	*after_env;

	if (*(ptr + 1) == '?')
		after_env = ptr + 2;
	else
	{
		after_env = ptr;
		while (!ft_strchr("> <\'\"|\0", *after_env))
			after_env++;
	}
	return (after_env);
}
