NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP

SRCS	=	main.c shell_loop.c \
			lexer/lexer.c lexer/lexer_utils.c \
			parser/parser.c parser/parser_utils.c \
			executor/executor.c executor/executor_utils.c executor/exec_pipeline.c \
			executor/apply_redir.c executor/builtin_cd.c executor/builtin_echo.c \
			executor/builtin_export.c executor/builtin_pwd.c \
			signals/signals.c signals/signals_exec.c \
			heredoc/heredoc.c \
			utils/error.c utils/free.c

OBJS_DIR = obj/

OBJS	= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS	= $(OBJS:.o=.d)

-include $(DEPS)

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= -I. -I$(LIBFT_DIR)


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)