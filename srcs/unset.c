#include "../includes/minishell.h"

int	unset_one(char *var, t_list *env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (env->next != NULL)
	{
		i = 0;
		while (((char *)env->next->content)[i] != '=')
			i++;
		if (ft_strncmp((char *)env->next->content, var, i) == 0)
		{
			tmp = env->next;
			env->next = env->next->next;
			free(tmp->content);
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	my_unset(char **var, t_list *env)
{
	if (var == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	while (*var != NULL)
	{
		unset_one(*var, env);
		var++;
	}
	return (0);
}
