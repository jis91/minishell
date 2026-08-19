/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 09:54:47 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/18 20:23:34 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, char **envp)
{
	int		i;
	char	**shell_env;
	int		env_length;

	env_length = count_env_length(envp);
	i = 0;
	shell_env = init_char_tab(env_length);
	while (envp[i])
	{
		shell_env[i] = ft_strdup(envp[i]);
		if (!shell_env[i])
		{
			free_char_tab(shell_env);
			fatal_error(NULL, NULL, "malloc failed", 1);
		}
		i++;
	}
	shell_env[i] = NULL;
	shell->env = shell_env;
	shell->exit_status = 0;
	return (0);
}

static void	process_line(char *line, t_shell *shell)
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
		shell->exit_status = executor(cmd, shell);
	}
	cleanup_cycle(tokens, cmd);
}

void	shell_loop(t_shell *shell)
{
	char	*line;
	char	*tmp;
	int		is_interactive;

	is_interactive = isatty(STDIN_FILENO);
	while (1)
	{
		setup_prompt_signals();
		line = NULL;
		if (is_interactive) 
			line = readline("minishell> ");
		else
		{
			tmp = get_next_line(STDIN_FILENO);
			if (tmp)
			{
				line = ft_strtrim(tmp, "\n");
				free(tmp);
			}
		}
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (!line)
		{
			if (is_interactive)
				write(1, "\n", 1);
			free_char_tab(shell->env);
			exit(shell->exit_status);
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		process_line(line, shell);
	}
}
