/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 11:50:07 by aganz             #+#    #+#             */
/*   Updated: 2026/09/02 16:25:10 by jstrasse         ###   ########.fr       */
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
