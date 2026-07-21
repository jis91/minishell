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
# include "libft/get_next_line/get_next_line_bonus.h"
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

extern volatile sig_atomic_t	g_signal;

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
	int				heredoc_fd;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}			t_cmd;

//EXECUTOR/PIPE STRUCT
typedef struct s_pipe_ctx
{
	int		**pipes;
	pid_t	*pids;
	int		count;
	int		index;
}	t_pipe_ctx;

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
	char	**env;
	int		exit_status;
}	t_shell;

//SHELL
int			init_shell(t_shell *shell, char **envp);
void		shell_loop(t_shell *shell);
//LEXER
t_token		*lexer(char *input);
void		handle_quotes(t_lexer *lexer);
void		handle_normal(t_lexer *lexer);
void		handle_operator(t_lexer *lexer);
void		add_token(t_lexer *lexer, t_token_type type);
void		flush_buffer(t_lexer *lexer, t_token_type type);
// PARSER
t_cmd		*parser(t_token *tokens);
int			count_token(t_token *tokens);
t_cmd		*init_cmd(int total_token);
int			validate_cmd(t_cmd *current);
t_cmd		*cleanup_parser(t_cmd *head, t_token *tokens);
int			parse_token(t_token **tokens,
				t_cmd **current, int *i, int total_token);
int			parse_redir(t_token **tokens, t_cmd *current);
//EXPANDER
int			has_dollar(char *string);
// SIGNALS AND HEREDOC
void		setup_prompt_signals(void);
void		setup_heredoc_signals(void);
void		setup_exec_signals(void);
void		reset_child_signals(void);
int			collect_heredoc(t_cmd *cmd_list);
//EXECUTOR
void		exec_external(t_cmd *cmd, t_shell *shell);
int			exec_builtin(t_cmd *cmd, t_shell *shell, t_builtin builtin);
int			exec_builtin(t_cmd *cmd, t_shell *shell, t_builtin builtin);
int			executor(t_cmd *cmds, t_shell *shell);
int			count_cmds(t_cmd *cmds);
char		*verify_path(char **directories, t_cmd *cmd);
char		*find_path(t_cmd *cmd, t_shell *shell);
int			**create_pipes(int count, t_shell *shell);
void		init_pipe_ctx(t_pipe_ctx *ctx);
int			fork_cmds(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell);
int			wait_cmds(t_pipe_ctx *ctx);
void		close_pipes(t_pipe_ctx *ctx);
int			exec_pipeline(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell);
int			exec_pipe_cmd(t_cmd *cmds, t_pipe_ctx *ctx, int i, t_shell *shell);
// APPLY REDIRECTIONS
int			apply_redir_in(t_redir *redir, t_shell *shell);
int			apply_redir_out(t_redir *redir, t_shell *shell);
int			apply_redir_append(t_redir *redir, t_shell *shell);
int			apply_redir_heredoc(t_redir *redir, t_shell *shell);
int			apply_single_redir(t_redir *redir, t_shell *shell);
int			apply_redirections(t_cmd *cmd, t_shell *shell);
//BUILTINS
t_builtin	check_builtin(t_cmd *cmd);
int			builtin_cd(t_cmd *cmd, t_shell *shell);
int			builtin_echo(t_cmd *cmd);
int			builtin_env(t_shell *shell);
int			builtin_exit(t_cmd *cmd, t_shell *shell);
int			builtin_export(t_cmd *cmd, t_shell *shell);
int			builtin_pwd(void);
int			builtin_unset(t_cmd *cmd, t_shell *shell);
//ENVIRONMENT
int			count_env_length(char **envp);
int			find_env_index(char **env, char *name);
int			add_env_var(t_shell *shell, char *name, char *value);
int			apply_to_env(t_shell *shell, char *name, char *value);
char		*get_env_value(char **env, char *name);

//UTILS
void		free_char_tab(char **tab);
void		free_int_tab(int **tab, int size);
void		free_tokens(t_token *tokens);
void		free_cmds(t_cmd *cmd);
void		free_redirs(t_redir *redirections);
void		cleanup_cycle(t_token *tokens, t_cmd *cmd);
int			syntax_error(void);
int			error(char *context, char *msg, int code);
void		fatal_error(char *context, char *msg, int code);

#endif