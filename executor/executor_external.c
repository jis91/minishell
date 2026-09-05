/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:32 by aganz             #+#    #+#             */
/*   Updated: 2026/08/25 22:27:09 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_execve_error(t_cmd *cmd, char *path)
{
	if (errno == EACCES || errno == EISDIR)
	{
		perror(cmd->args[0]);
		free(path);
		exit(126);
	}
	perror(cmd->args[0]);
	free (path);
	exit (127);
}

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	reset_child_signals();
	if (apply_redirections(cmd) == -1)
		exit(1);
	if (!cmd->args[0])
		exit(0);
	path = find_path(cmd, shell);
	if (!path)
	{
		if (errno == EACCES || errno == EISDIR)
			exit(126);
		if (errno == EINVAL)
			exit(2);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	handle_execve_error(cmd, path);
}
