#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef struct s_tokens
{
	t_list	*env;	
	char	*ptr;
	char	*input;
	char	*crt_tkn;
	char	**tokens;
}	t_tokens;

void	dollar_handler(t_tokens *tkn);
void	add_chr_tkn(t_tokens *tkn);
void	quote_handle(t_tokens *tkn);
int		is_spec(char input);
#endif
