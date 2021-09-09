#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "minishell.h"

void	print_sorted(t_list *env);
int		find_symbol(char *str, char sym);
char	*get_env_val(char *env_name, t_list *envlist);
#endif
