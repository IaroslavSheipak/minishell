#include "../includes/minishell.h"

char	*replace_one(char *input, char *ptr, t_list *envlist, int dquot)
{
	char	*before;
	char	*after_env;
	char	*env_val;
	char	*first;
	char	*second;

	before = ft_substr(input, 0, ptr - input);
	after_env = get_after_env(ptr);
	env_val = env_val_name(input, ptr, after_env, envlist);
	first = ft_strjoin(before, env_val);
	after_env = ft_strdup(after_env);
	second = replace_envs(after_env, envlist, dquot);
	if (input)
		free(input);
	input = ft_strjoin(first, second);
	if (*env_val)
		free(env_val);
	free(second);
	free(first);
	free(before);
	return (input);
}

char	*replace_envs(char *input, t_list *envlist, int dquot)
{
	char	*ptr;

	if (!input)
		return (NULL);
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\"')
			dquot = !dquot;
		else if (*ptr == '\'' && !dquot)
		{
			ptr = ft_strchr(ptr + 1, '\'');
			ptr++;
			continue ;
		}
		if (*ptr == '<' && *(ptr + 1) == '<' && !dquot)
			ptr += 3;
		if (*ptr == '$' )
			return (replace_one(input, ptr, envlist, dquot));
		ptr++;
	}
	return (input);
}

char	*add_token(char ***arr_tokens, char *input, char *start, char *end)
{
	char	*res;

	res = ft_substr(input, start - input, end - start + 1);
	arraddelem(arr_tokens, res);
	free(res);
	return (end + 1);
}

char	*skip_char(char *str, char sym)
{
	while (*str == sym)
		str++;
	return (str);
}

char	*split_to_tokens(char *input, char ***arr_tokens)
{
	char	*start_of_token;
	char	*end_of_token;

	start_of_token = input;
	while (*start_of_token != '\0')
	{
		start_of_token = skip_char(start_of_token, ' ');
		end_of_token = start_of_token;
		while (!ft_strchr("> <|\0", *(start_of_token)))
		{
			if (ft_strchr("\"\'", *end_of_token))
				end_of_token = ft_strchr(end_of_token + 1, *end_of_token);
			if (ft_strchr("> <|\0", *(end_of_token + 1)))
				break ;
			end_of_token++;
		}
		if (ft_strchr("<>", *start_of_token) && *start_of_token
			== *(start_of_token + 1))
			end_of_token++;
		if (*start_of_token != '\0')
			start_of_token = add_token(arr_tokens,
					input, start_of_token, end_of_token);
	}
	free(input);
	return (NULL);
}
