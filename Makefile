CC		:= gcc
CFLAGS		:= -g -Wall -Wextra -Werror	
NAME		:=	minishell
SRCS_DIR	:=	srcs/
OBJS		:=	main.o	\
				main_utils.o \
				echo.o	\
				cd.o	\
				pwd.o	\
				env.o	\
				export.o	\
				unset.o		\
				exit.o		\
				parser.o	\
				parser_utils.o	\
				converter.o	\
				exec_coms.o \
				exec_coms_utils.o \
				exec_pipe.o \
				exec_redir.o \
				sig_handlers.o \
				token_to_ast.o \
				list_utils.o \
				find_exec.o \
				ft_strcmp.o	\
				env_utils.o
OBJS		:=	$(addprefix ${SRCS_DIR}, ${OBJS})

deps 		:= $(patsubst %.o,%.d,$(OBJS))

all:		$(NAME)

$(NAME):	$(OBJS)
		cd Libft/ && make && make bonus && make clean
		gcc $(CFLAGS) $(OBJS) -o $(NAME)  -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1/lib/ -I/Users/${USER}/.brew/Cellar/readline/8.1/include-LLibft/ -LLibft/ -lft -L.
-include $(deps)

DEPSFLAGS 	= -MMD -MF $(@:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(DEPSFLAGS) -o $(<:.c=.o)

clean:
	rm -f $(OBJS) $(deps)
	

fclean: clean 
	rm -f $(NAME)
	cd Libft/ && make fclean

re: fclean all

.PHONY: all, clean, fclean, re
