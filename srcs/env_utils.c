#include "../includes/minishell.h"

char	*get_env_val(char *env_name, t_list *envlist)
{
	t_list	*ptr;
	char	*equal_pos;

	if (*env_name == '?')
		return (ft_itoa(g_excd_sig.excode));
	ptr = envlist;
	while (ptr)
	{
		equal_pos = ft_strchr((char *)ptr->content, '=');
		*equal_pos = '\0';
		if (0 == ft_strcmp(env_name, ptr->content))
		{
			*equal_pos = '=';
			return (ft_strdup(equal_pos + 1));
		}
		*equal_pos = '=';
		ptr = ptr->next;
	}
	return ("\0");
}

int	find_symbol(char *str, char sym)
{
	int	res;

	res = 0;
	while (str[res] != '\0' && str[res] != sym)
	{
		res++;
	}
	if (str[res] == '\0')
		return (-1);
	return (res);
}

void	print_all_sorted(t_list *sorted)
{
	int	i;

	while (sorted != NULL)
	{
		i = find_symbol(sorted->content, '=');
		((char *)sorted->content)[i] = '\0';
		printf("declare -x %s%s%s%s\n", (char *)sorted->content, "=\"",
			&((char *)sorted->content)[i + 1], "\"");
		((char *)sorted->content)[i] = '=';
		sorted = sorted->next;
	}
}

void	print_sorted(t_list *env)
{
	t_list	*sorted;
	t_list	*tmp;
	t_list	*free_sort;

	if (env)
	{
		tmp = env;
		sorted = ft_lstnew(tmp->content);
		tmp = tmp->next;
		while (tmp != NULL)
		{
			ft_lstadd_front(&sorted, ft_lstnew(tmp->content));
			tmp = tmp->next;
		}
		free_sort = sorted;
		print_all_sorted(sorted);
	}
	ft_lstclear(&free_sort, free);
}
