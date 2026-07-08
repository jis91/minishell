/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:26 by aganz             #+#    #+#             */
/*   Updated: 2026/07/08 12:44:46 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		status;

	path = find_path(cmd, shell);
	if (!path)
		return (127);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		execve(path, cmd->args, shell->env);
		free (path);
		return (-1);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free (path);
		return (WEXITSTATUS(status));
	}
}

int	exec_builtin(t_cmd *cmd, t_shell *shell, t_builtin builtin)
{
	if (builtin == BUILTIN_ECHO)
		return (ft_builtin_echo(cmd, shell));
	if (builtin == BUILTIN_CD)
		return (ft_builtin_cd(cmd, shell));
	if (builtin == BUILTIN_PWD)
		return (ft_builtin_pwd(cmd, shell));
	if (builtin == BUILTIN_EXPORT)
		return (ft_builtin_export(cmd, shell));
	if (builtin == BUILTIN_UNSET)
		return (ft_builtin_unset(cmd, shell));
	if (builtin == BUILTIN_ENV)
		return (ft_builtin_env(cmd, shell));
	if (builtin == BUILTIN_EXIT)
		return (ft_builtin_exit(cmd, shell));
	return (1);
}

int	executor(t_cmd *cmds, t_shell *shell)
{
	t_cmd		*current;
	int			count;
	t_builtin	builtin;

	count = count_cmds(cmds);
	current = cmds;
	if (!cmds)
		return (1);
		builtin = check_builtin(cmds);
	if (count == 1)
	{
		if (builtin != NOT_BUILTIN)
			exec_builtin()
		else
			exec_external()
	}
	else
	{
		while (current)
		// code
		current = current->next;
	}
}
