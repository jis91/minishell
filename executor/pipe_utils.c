/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:57:12 by aganz             #+#    #+#             */
/*   Updated: 2026/07/23 16:27:53 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**create_pipes(int count, t_shell *shell)
{
	int	**pipes;
	int	i;

	(void)shell;
	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_int_tab(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free(pipes[i]);
			free_int_tab(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	init_pipe_ctx(t_pipe_ctx *ctx)
{
	ctx->pipes = NULL;
	ctx->pids = NULL;
	ctx->count = 0;
	ctx->index = 0;
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

void	close_child_pipes(t_pipe_ctx *ctx, int i)
{
	int	j;

	j = 0;
	while (j < ctx->count -1)
	{
		if (!(i > 0 && j == i - 1))
			close(ctx->pipes[j][0]);
		if (!(i < ctx->count - 1 && j == i))
			close(ctx->pipes[j][1]);
		j++;
	}
}