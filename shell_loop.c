/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 09:54:47 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/11 10:13:17 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_prompt_signals();
		line = readline("minishell> ");
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
			free(line);
			continue ;
		}
		if (!line)
			exit(shell->exit_status);
		if (ft_strlen(line) > 0)
			add_history(line);
		process_line(line, shell);
	}
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer(line);
	free(line);
	cmd = parser(tokens);
	if (!cmd)
		return ;
	if (!collect_heredoc(cmd))
	{
		expander();
		executor();
	}
	cleanup_cycle(tokens, cmd);
}
