/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:40:49 by aganz             #+#    #+#             */
/*   Updated: 2026/07/17 09:47:58 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_cmds(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell)
{
	t_cmd	*current;
	int		i;

	current = cmds;
	i = 0;
	while (current)
	{
		ctx->pids[i] = fork();
		if (ctx->pids[i] == -1)
		{
			free_int_tab(ctx->pipes, ctx->count - 1);
			perror("malloc failed");
			exit(1);
		}
		if (ctx->pids[i] == 0)
			exec_pipe_cmd(current, ctx, i, shell);
		current = current->next;
		i++;
	}
	return (0);
}

int	wait_cmds(t_pipe_ctx *ctx)
{
	int	i;
	int	status;

	i = 0;
	while (i < ctx->count)
	{
		waitpid(ctx->pids[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}

int	exec_pipeline(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell)
{
	ctx->count = count_cmds(cmds);
	ctx->pipes = create_pipes(ctx->count, shell);
	ctx->pids = malloc(sizeof(pid_t) * ctx->count);
	if (!ctx->pids)
	{
		free_int_tab(ctx->pipes, ctx->count - 1);
		perror("malloc failed");
		exit(1);
	}
	fork_cmds(cmds, ctx, shell);
	close_pipes(ctx);
	free_int_tab(ctx->pipes, ctx->count - 1);
	free(ctx->pids);
	return (wait_cmds(ctx));
}

int	exec_pipe_cmd(t_cmd *cmds, t_pipe_ctx *ctx, int i, t_shell *shell)
{
	t_builtin	builtin;

	if (i > 0)
	{
		if (dup2(ctx->pipes[i - 1][0], 0) == -1)
			exit(1);
	}
	if (i < ctx->count - 1)
	{
		if (dup2(ctx->pipes[i][1], 1) == -1)
			exit(1);
	}
	close_pipes(ctx);
	if (apply_redirections(cmds, shell) == -1)
		exit (1);
	builtin = check_builtin(cmds);
	if (builtin != NOT_BUILTIN)
		exit(exec_builtin(cmds, shell, builtin));
	else
		exec_external(cmds, shell);
	exit(1);
}
