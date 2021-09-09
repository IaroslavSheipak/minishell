#include "../includes/minishell.h"

t_ast	*add_to_redir_pipe(t_ast *res, t_ast *node)
{
	if (res->type == REDIR)
	{
		if (res->left == NULL)
			res->left = add_node(res->left, node);
		else
			res->right = add_node(res->right, node);
	}
	if (res->type == PIPE)
	{
		if (res->right != NULL)
			res->left = add_node(res->left, node);
		else
			res->right = add_node(res->right, node);
	}
	return (res);
}

t_ast	*add_node(t_ast *tree, t_ast *node)
{
	t_ast	*res;

	if (tree == NULL)
		return (node);
	res = tree;
	if (node->type < res->type)
	{
		node->right = res;
		res = node;
	}
	else if (node->type == res->type)
	{
		if (node->type == PIPE || node->type == SEMICOL)
		{
			node->right = res;
			res = node;
		}
		else
			res->right = add_node(res->right, node);
	}
	else
		res = add_to_redir_pipe(res, node);
	return (res);
}

char	*ft_quottrim(char *line)
{
	ssize_t	*utils;

	utils = ft_calloc(sizeof(ssize_t), 3);
	while ((unsigned)utils[0] < ft_strlen(line))
	{
		if (line[utils[0]] == '\'' && utils[2] == 0)
			utils[2] = 1;
		else if (line[utils[0]] == '\'' && utils[2] == 1)
			utils[2] = 0;
		else if (line[utils[0]] == '\"' && utils[2] == 0)
			utils[2] = 2;
		else if (line[utils[0]] == '\"' && utils[2] == 2)
			utils[2] = 0;
		else if (line[utils[0]] != '\'' && line[utils[0]] != '"')
			line[utils[1]++] = line[utils[0]];
		else if (line[utils[0]] == '"' && utils[2] == 1)
			line[utils[1]++] = '"';
		else if (line[utils[0]] == '\'' && utils[2] == 2)
			line[utils[1]++] = '\'';
		utils[0]++;
	}
	if (utils[1] >= 0)
		line[utils[1]] = 0;
	free(utils);
	return (line);
}

t_ast	*create_node(char *token)
{
	t_ast	*res;	

	res = malloc(sizeof(t_ast));
	if (token == NULL)
		return (NULL);
	else if (!('>' == *token) * ft_strcmp(">>", token)
		* ft_strcmp("<", token) * ft_strcmp("<<", token) == 0)
	{
		res->type = REDIR;
		res->exec = redir_exec;
	}
	else if (ft_strcmp("|", token) == 0)
	{	
		res->type = PIPE;
		res->exec = pipe_exec;
	}		
	else
	{	
		res->type = WORD;
		res->exec = cmd_exec;
	}
	res->token = token;
	res->left = NULL;
	res->right = NULL;
	return (res);
}

t_ast	*generate_ast(char **tokens)
{
	t_ast	*res;
	t_ast	*node;

	res = NULL;
	while (*tokens != NULL)
	{
		node = create_node(*tokens);
		res = add_node(res, node);
		tokens++;
	}
	return (res);
}
