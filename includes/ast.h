#ifndef AST_H
# define AST_H

# define WORD 2
# define REDIR 1
# define PIPE 0
# define SEMICOL -1

# include "minishell.h"

typedef struct s_ast
{
	char			*token;
	int				prior;
	int				type;
	void			(*exec)();
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast	*add_node(t_ast *tree, t_ast *node);
t_ast	*create_node(char *token);
t_ast	*generate_ast(char **tokens);
void	exec_builtin(char *name, char **args, t_list *envlist);
int		my_execve(char *file, char **args, t_list *envlist);
char	**collect_args(t_ast *self);
int		is_builtin(t_ast *self);
void	cmd_exec(t_ast	*self, t_list *envlist);
int		change_in(t_ast *node, int *fd_redir, t_list *envlist);
int		change_out(t_ast *node, int *fd_redir, t_list *envlist);
void	pipe_exec(t_ast *self, t_list *envlist);
void	two_right_exec(t_ast *self);
void	one_right_exec(t_ast *self);
void	one_left_exec(t_ast *self);
void	redir_exec(t_ast	*self, t_list *envlist);
void	semicol_exec(t_ast *node, t_list *envlist);
#endif
