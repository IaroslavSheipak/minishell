#include "../includes/minishell.h"

int	check_ast(t_ast *tree)
{
	if (tree == NULL)
		return (1);
	if (tree->type == PIPE || tree->type == REDIR)
		if (tree->left == NULL)
			return (0);
	if (!check_ast(tree->right))
		return (0);
	if (!check_ast(tree->left))
		return (0);
	return (1);
}

void	exec_ast(t_ast *tree, t_list *envlist)
{
	int	orig_fd[2];

	orig_fd[0] = dup(0);
	orig_fd[1] = dup(1);
	if (!check_ast(tree))
	{
		ft_putstr_fd("Error in commands\n", 1);
		return ;
	}
	tree->exec(tree, envlist);
	dup2(orig_fd[0], 0);
	dup2(orig_fd[1], 1);
	close(orig_fd[0]);
	close(orig_fd[1]);
}

void	print_ast(t_ast *tree)
{
	printf("%s\n", tree->token);
	if (tree->left != NULL)
	{	
		printf("left of %s: ", tree->token);
		print_ast(tree->left);
	}	
	if (tree->right != NULL)
	{	
		printf("right of %s: ", tree->token);
		print_ast(tree->right);
	}
}

void	free_ast(t_ast *ast)
{
	if (ast->right)
		free_ast(ast->right);
	if (ast->left)
		free_ast(ast->left);
	free(ast);
}

char	*handle_two_left(char *str, int redir_fd, t_list *envlist)
{
	char	*tmp;

	tmp = ft_strjoin("\"", str);
	free(str);
	str = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = replace_envs(str, envlist, 0);
	str = ft_strtrim(tmp, "\"");
	free(tmp);
	ft_putstr_fd(str, redir_fd);
	ft_putchar_fd('\n', redir_fd);
	free(str);
	return (NULL);
}
