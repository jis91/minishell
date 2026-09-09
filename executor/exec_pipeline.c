/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:40:49 by aganz             #+#    #+#             */
/*   Updated: 2026/09/07 20:54:07 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			perror("fork");
			return (i);
		}
		if (ctx->pids[i] == 0)
			exec_pipe_cmd(current, ctx, i, shell);
		current = current->next;
		i++;
	}
	return (i);
}

int	wait_cmds(t_pipe_ctx *ctx, int forked_successful)
{
	int	i;
	int	status;

	i = 0;
	while (i < forked_successful)
	{
		waitpid(ctx->pids[i], &status, 0);
		i++;
	}
	if (forked_successful < ctx->count)
		return (1);
	else
		return (get_exit_status(status));
}

int	exec_pipeline(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell)
{
	int	result;
	int	forked_succesful;

	ctx->count = count_cmds(cmds);
	ctx->pipes = create_pipes(ctx->count, shell);
	if (!ctx->pipes)
		return (1);
	ctx->pids = malloc(sizeof(pid_t) * ctx->count);
	if (!ctx->pids)
	{
		free_int_tab(ctx->pipes, ctx->count - 1);
		fatal_error(shell, NULL, "malloc failed", 1);
	}
	ctx->head = cmds;
	setup_exec_signals();
	forked_succesful = fork_cmds(cmds, ctx, shell);
	close_pipes(ctx);
	free_int_tab(ctx->pipes, ctx->count - 1);
	result = wait_cmds(ctx, forked_succesful);
	free(ctx->pids);
	setup_prompt_signals();
	return (result);
}

static void	setup_pipe_fds(t_pipe_ctx *ctx, int i)
{
	if (i > 0)
	{
		if (dup2(ctx->pipes[i - 1][0], 0) == -1)
			exit(1);
		close(ctx->pipes[i - 1][0]);
	}
	if (i < ctx->count - 1)
	{
		if (dup2(ctx->pipes[i][1], 1) == -1)
			exit(1);
		close(ctx->pipes[i][1]);
	}
}

void	exec_pipe_cmd(t_cmd *cmds, t_pipe_ctx *ctx, int i, t_shell *shell)
{
	t_builtin	builtin;
	int			status;

	reset_child_signals();
	setup_pipe_fds(ctx, i);
	close_child_pipes(ctx, i);
	builtin = check_builtin(cmds);
	if (builtin != NOT_BUILTIN)
	{
		if (apply_redirections(cmds) == -1)
			cleanup_and_exit(ctx, cmds, shell, 1);
		status = exec_builtin(cmds, shell, builtin);
		cleanup_and_exit(ctx, cmds, shell, status);
	}
	else
		exec_external(cmds, shell, ctx);
}
