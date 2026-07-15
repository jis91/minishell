/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 22:29:11 by aganz             #+#    #+#             */
/*   Updated: 2026/07/15 22:29:50 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
