#include "../includes/minishell.h"

int	my_echo(char **line)
{
	int	nflag;

	nflag = 0;
	line++;
	if (*line == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ft_strncmp("-n", *line, ft_strlen(*line)) == 0)
		nflag = 1;
	line += nflag;
	while (*line != NULL)
	{
		ft_putstr_fd(*line, 1);
		if (*(line + 1) != NULL)
			ft_putchar_fd(' ', 1);
		line++;
	}
	if (!nflag)
		ft_putchar_fd('\n', 1);
	return (0);
}
