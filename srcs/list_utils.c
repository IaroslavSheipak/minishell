#include "../includes/minishell.h"

char	**listtoarr(t_list *env)
{
	char	**envarr;

	envarr = NULL;
	while (env)
	{
		arraddelem(&envarr, env->content);
		env = env->next;
	}
	return (envarr);
}

char	**my_arr_realloc(char **ptr, size_t newsize)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc((newsize + 1) * sizeof(char *));
	while (ptr[i])
	{
		res[i] = ft_strdup(ptr[i]);
		i++;
	}
	if (!res)
		error_exit();
	if (ptr)
		free_arr(ptr);
	return (res);
}

void	arraddelem(char ***array, char *string)
{
	int	arrsize;

	arrsize = 0;
	if (*array == NULL)
	{
		*array = ft_calloc(2, sizeof(char *));
		**array = ft_strdup(string);
		*(*array + 1) = NULL;
		return ;
	}
	while ((*array)[arrsize])
		arrsize++;
	*array = my_arr_realloc(*array, arrsize + 1);
	((*array)[arrsize]) = ft_strdup(string);
	((*array)[arrsize + 1]) = NULL;
}

void	concat_arr(char ***a, char **b)
{
	int	i;

	i = 0;
	if (b == NULL)
		return ;
	while (b[i])
	{
		arraddelem(a, b[i]);
		i++;
	}
	if (b)
		free(b);
}
