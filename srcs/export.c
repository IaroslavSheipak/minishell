#include "../includes/minishell.h"

int	export_one(char *varval, t_list *env)
{
	int		i;
	t_list	*tmp;
	int		eq;

	i = 0;
	eq = 0;
	while (varval[eq + i] != '=' && varval[eq + i] != '\0')
		eq++;
	if (varval[eq] == '\0')
		return (1);
	if (ft_strchr("= ", varval[eq + 1]) || varval[eq - 1] == ' ')
		return (1);
	tmp = env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->content, &varval[i], eq + 1))
		{
			free(tmp->content);
			tmp->content = ft_strdup(&varval[i]);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&env, ft_lstnew(ft_strdup(&varval[i])));
	return (0);
}

void	sort_alpha(t_list **alst)
{
	t_list	*list;
	char	*tmp;

	list = *alst;
	if (list != NULL)
	{
		while (list != NULL && list->next != NULL)
		{
			if (ft_strcmp(list->content, list->next->content) > 0)
			{
				tmp = list->content;
				list->content = list->next->content;
				list->next->content = tmp;
			}
			list = list->next;
		}
	}
}

void	list_add(t_list **alst, t_list *newElement)
{
	t_list	*temp;

	temp = *alst;
	if (newElement)
	{
		newElement->next = *alst;
		*alst = newElement;
		sort_alpha(alst);
	}
}

int	check_export(char **varval)
{
	while (*varval)
	{
		if (ft_isdigit(**varval))
		{
			ft_putstr_fd("minishell: export: \'", 2);
			ft_putstr_fd(*varval, 2);
			ft_putstr_fd("\' : not a valid identifier", 2);
			return (1);
		}
		varval++;
	}
	return (0);
}

int	my_export(char **varval, t_list *env)
{
	if (varval[1] == NULL)
	{
		print_sorted(env);
		return (0);
	}
	while (*varval != NULL)
	{
		if (check_export(varval))
			return (1);
		export_one(*varval, env);
		varval++;
	}
	return (0);
}
