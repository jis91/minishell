/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:30:04 by aganz             #+#    #+#             */
/*   Updated: 2026/07/10 15:30:04 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redir_in(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redir_out(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redir_append(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redir_heredoc(t_redir *redir, t_shell *shell)
{
	(void)shell;
	if (dup2(redir->heredoc_fd, 0) == -1)
	{
		close(redir->heredoc_fd);
		return (-1);
	}
	close(redir->heredoc_fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			if (apply_redir_in(redir, shell) == -1)
				return (-1);
		}
		else if (redir->type == TOKEN_REDIR_OUT)
		{
			if (apply_redir_out(redir, shell) == -1)
				return (-1);
		}
		else if (redir->type == TOKEN_REDIR_APP)
		{
			if (apply_redir_append(redir, shell) == -1)
				return (-1);
		}
		else if (redir->type == TOKEN_HEREDOC)
		{
			if (apply_redir_heredoc(redir, shell) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
