/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 09:54:47 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/07 11:24:51 by aganz            ###   ########.fr       */
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
	shell_env = ft_calloc(sizeof(char *), (env_length + 1));
	if (!shell_env)
		return (1);
	while (envp[i])
	{
		shell_env[i] = ft_strdup(envp[i]);
		if (!shell_env[i])
		{
			free_char_tab(shell_env);
			return (1);
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
	if (!collect_heredoc(cmd))
	{
		expander(cmd, shell);
		if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		{
			cleanup_cycle(tokens, cmd);
			return ;
		}
		shell->exit_status = executor(cmd, shell);
	}
	cleanup_cycle(tokens, cmd);
}

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
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			free_char_tab(shell->env);
			exit(shell->exit_status);
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		process_line(line, shell);
	}
}
