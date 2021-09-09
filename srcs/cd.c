#include "../includes/minishell.h"

void	change_en_var(t_list *var, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (((char *)var->content)[i] != '=')
		i++;
	((char *)var->content)[i + 1 ] = '\0';
	res = ft_strjoin(((char *)var->content), str);
	free(var->content);
	var->content = res;
}

void	change_var(t_list *envlist, char *newvar, char *varname)
{
	t_list	*ptr;

	ptr = envlist;
	while (ptr != NULL)
	{
		if (ft_strncmp((char *)ptr->content, varname, ft_strlen(varname)) == 0)
		{
			change_en_var(ptr, newvar);
		}
		ptr = ptr->next;
	}
}

int	handle_inval_cd(char *path, char *oldpwd)
{
	write(2, "cd: no such file or directory: ", 32);
	write(2, path, ft_strlen(path));
	write(1, "\n", 1);
	free(oldpwd);
	return (1);
}

int	my_cd(char **path, t_list *envlist)
{
	int		ch;
	char	*tmp;
	char	*oldpwd;

	path++;
	if (*path == NULL)
		tmp = get_env_val("HOME", envlist);
	else
		tmp = ft_strdup(*path);
	tmp = skip_char(tmp, ' ');
	oldpwd = getcwd(NULL, 0);
	ch = chdir(tmp);
	free(tmp);
	if (ch < 0)
		return (handle_inval_cd(*path, oldpwd));
	change_var(envlist, oldpwd, "OLDPWD");
	free(oldpwd);
	tmp = getcwd(NULL, 0);
	change_var(envlist, tmp, "PWD");
	free(tmp);
	return (0);
}
