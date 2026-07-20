/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:40:49 by aganz             #+#    #+#             */
/*   Updated: 2026/07/20 22:50:32 by aganz            ###   ########.fr       */
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
			perror("fork");
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
	int	result;

	ctx->count = count_cmds(cmds);
	ctx->pipes = create_pipes(ctx->count, shell);
	ctx->pids = malloc(sizeof(pid_t) * ctx->count);
	if (!ctx->pids)
	{
		free_int_tab(ctx->pipes, ctx->count - 1);
		fatal_error(NULL, "malloc failed", 1);
	}
	setup_exec_signals();
	fork_cmds(cmds, ctx, shell);
	close_pipes(ctx);
	free_int_tab(ctx->pipes, ctx->count - 1);
	free(ctx->pids);
	result = wait_cmds(ctx);
	setup_prompt_signals();
	return (result);
}

int	exec_pipe_cmd(t_cmd *cmds, t_pipe_ctx *ctx, int i, t_shell *shell)
{
	t_builtin	builtin;

	reset_child_signals();
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
	return (0);
}
