/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:42:16 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/04 12:42:16 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>

//LEXER ENUM AND STRUCT
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APP,
	TOKEN_HEREDOC,
}		t_token_type;

typedef enum e_state
{
	NORMAL,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
}			t_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}			t_token;

typedef struct s_lexer
{
	char	*input;
	char	*buffer;
	t_state	state;
	int		buffer_index;
	int		i;
	t_token	*head;
	t_token	*tail;
}			t_lexer;

//PARSER STRUCT
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}			t_cmd;

/*Executor*/
typedef enum e_builtin
{
	NOT_BUILTIN,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin;

/*Shell structure*/
typedef struct s_shell
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**env;
	int		exit_status;
}	t_shell;

//LEXER
t_token	*lexer(char *input);
void	handle_quotes(t_lexer *lexer);
void	handle_normal(t_lexer *lexer);
void	handle_operator(t_lexer *lexer);
void	add_token(t_lexer *lexer, t_token_type type);
void	flush_buffer(t_lexer *lexer, t_token_type type);
void	free_tokens(t_token *tokens);
// PARSER
t_cmd	*parser(t_token *tokens);
int		count_token(t_token *tokens);
t_cmd	*init_cmd(int total_token);
int		validate_cmd(t_cmd *current);
t_cmd	*cleanup_parser(t_cmd *head, t_token *tokens);
int		parse_token(t_token **tokens, t_cmd **current, int *i, int total_token);
int		parse_redir(t_token **tokens, t_cmd *current);
void	free_cmds(t_cmd *cmd);
void	free_redirs(t_redir *redirections);
int		syntax_error(void);
//EXECUTOR
int			exec_external(t_cmd *cmd, t_shell *shell);
int			exec_builtin(t_cmd *cmd, t_shell *shell, t_builtin builtin);
int			executor(t_cmd *cmds, t_shell *shell);
int			count_cmds(t_cmd *cmds);
t_builtin	check_builtin(t_cmd *cmd);
char		*verify_path(char **directories, t_cmd *cmd);
char		*find_path(t_cmd *cmd, t_shell *shell);
int			**ft_create_pipes(int count, t_shell *shell);
#endif