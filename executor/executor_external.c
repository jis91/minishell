/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:32 by aganz             #+#    #+#             */
/*   Updated: 2026/09/06 21:09:42 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		code = 126;
	else
		code = 127;
	perror(cmd->args[0]);
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
