/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:32 by aganz             #+#    #+#             */
/*   Updated: 2026/09/09 08:54:55 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_access(char *path, char **fallback)
{
	if (access(path, X_OK) == 0)
	{
		if (path != (*fallback))
			free((*fallback));
		return (0);
	}
	else
	{
		if (access(path, F_OK) == 0)
		{
			if ((*fallback) == NULL)
				(*fallback) = path;
			else
				free(path);
			return (-1);
		}
		else
		{
			if (path != (*fallback))
				free(path);
			return (1);
		}
	}
}

void	cleanup_and_exit(t_pipe_ctx *ctx, t_cmd *cmd, t_shell *shell,
			int status)
{
	if (ctx)
	{
		free_int_tab(ctx->pipes, ctx->count - 1);
		free(ctx->pids);
		free_cmds(ctx->head);
	}
	else
		free_cmds(cmd);
	free_char_tab(shell->env);
	exit(status);
}

static void	handle_execve_error(t_cmd *cmd, char *path, t_pipe_ctx *ctx,
			t_shell *shell)
{
	int	code;

	if (errno == EACCES || errno == EISDIR)
	{
		code = 126;
		error(cmd->args[0], "Permission denied", code);
	}
	else
	{
		code = 127;
		error(cmd->args[0], "command not found", code);
	}
	free (path);
	cleanup_and_exit(ctx, cmd, shell, code);
}

void	exec_external(t_cmd *cmd, t_shell *shell, t_pipe_ctx *ctx)
{
	char	*path;
	int		code;

	reset_child_signals();
	if (apply_redirections(cmd) == -1)
		cleanup_and_exit(ctx, cmd, shell, 1);
	if (!cmd->args[0])
		cleanup_and_exit(ctx, cmd, shell, 0);
	path = find_path(cmd, shell);
	if (!path)
	{
		if (errno == EACCES || errno == EISDIR)
			code = 126;
		else if (errno == EINVAL)
			code = 2;
		else
			code = 127;
		cleanup_and_exit(ctx, cmd, shell, code);
	}
	execve(path, cmd->args, shell->env);
	handle_execve_error(cmd, path, ctx, shell);
}
