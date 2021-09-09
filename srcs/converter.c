#include "../includes/minishell.h"

t_list	*converter(char **envp)
{
	int		i;
	t_list	*head;

	head = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (head);
}
