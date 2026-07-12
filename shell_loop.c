/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 09:54:47 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/12 14:31:48 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, char **envp)
{
	int		i;
	char	**shell_env;
	int		env_length;

	i = 0;
	while (envp[i])
		i++;
	env_length = i;
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
	return (0);
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
