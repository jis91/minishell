/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:40:49 by aganz             #+#    #+#             */
/*   Updated: 2026/07/10 15:49:10 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipes(int count, t_shell *shell)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (i > 0)
			{
				i--;
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		count;
	int		**pipes;
	pid_t	*pid;
	int		status;

	count = ft_count_cmds(cmds, shell);
	pipes = create_pipes(count - 1);
	while (cmds)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			dup2();
			close()
			executor(cmds, shell);
		}
		if (pid > 0)
		{
			close();
			waitpid(pid, &status, 0);
		}
	}
	return (WEXITSTATUS(status));
}

void	init_pipe_ctx(t_pipe_ctx *ctx)
{
	ctx->pipes = NULL;
	ctx->pids = NULL;
	ctx->count = 0;
	ctx->index = 0;
}

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
			ft_fatal_error(shell, "fork failed in fork_cmds");
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

void	close_pipes(t_pipe_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->count - 1)
	{
		close(ctx->pipes[i][0]);
		close(ctx->pipes[i][1]);
		i++;
	}
}

int	exec_pipeline(t_cmd *cmds, t_pipe_ctx *ctx, t_shell *shell)
{
	ctx->count = count_cmds(cmds);
	ctx->pipes = ft_create_pipes(ctx->count, shell);
	ctx->pids = malloc(sizeof(pid_t) * ctx->count);
	if (!ctx->pids)
	{
		free_int_tab(ctx->pipes, ctx->count - 1);
		fatal_error(shell, "malloc failed in exec_pipeline");
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
		if (dup2(ctx->pipes[i-1][0], 0) == -1)
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
		exit(exec_external(cmds, shell));
}
