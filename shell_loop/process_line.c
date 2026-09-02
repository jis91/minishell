/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   process_line.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: aganz <aganz@student.42lausanne.ch>           +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/09/02 11:50:07 by aganz          #+#    #+#                */
/*   Updated: 2026/09/02 11:50:29 by aganz          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!collect_heredoc(cmd, shell))
	{
		expander(cmd, shell);
		remove_empty_args(cmd);
		if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
			return ;
		shell->exit_status = executor(cmd, shell);
	}
}

static t_cmd	*build_cmd(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (only_whitespace_empty(line))
		return (NULL);
	tokens = lexer(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	cmd = parser(tokens);
	if (cmd)
		free_tokens(tokens);
	if (!cmd)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	return (cmd);
}

void	process_line(char *line, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = build_cmd(line, shell);
	free(line);
	if (!cmd)
		return ;
	run_cmd(cmd, shell);
	free_cmds(cmd);
}

/*static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!only_whitespace_empty(line))
		tokens = lexer(line);
	else
	{
		free(line);
		return ;
	}
	free(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return ;
	}
	cmd = parser(tokens);
	if (!cmd)
	{
		shell->exit_status = 2;
		return ;
	}
	if (!collect_heredoc(cmd, shell))
	{
		expander(cmd, shell);
		remove_empty_args(cmd);
		if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		{
			cleanup_cycle(tokens, cmd);
			return ;
		}
		shell->exit_status = executor(cmd, shell);
	}
	cleanup_cycle(tokens, cmd);
}*/