#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_token_lst
{
	struct s_tokens_list	*next;
	char					*token;
	int						type;
}							t_token_lst;
#endif
