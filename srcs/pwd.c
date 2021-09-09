#include "../includes/minishell.h"

int	my_pwd(void)
{
	char	*abs_path;
	char	*res;

	abs_path = NULL;
	res = getcwd(NULL, 0);
	if (res == NULL)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	write(1, res, ft_strlen(res));
	write(1, "\n", 1);
	free(res);
	return (1);
}
