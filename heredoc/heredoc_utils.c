/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:04:38 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/25 22:29:18 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc_signal(char *line, int fd_write, int fd_read)
{
	if (g_signal == SIGINT)
	{
		free(line);
		g_signal = 0;
		close(fd_write);
		close(fd_read);
		return (1);
	}
	return (0);
}

void	write_heredoc_line(char *line, t_redir *redir,
		t_shell *shell, int fd_write)
{
	char	*expanded;

	if (redir->should_expand)
	{
		expanded = assembler(line, shell);
		write(fd_write, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd_write, line, ft_strlen(line));
}

int	prepare_delimiter(t_redir *redir)
{
	char	*clean;

	clean = strip_quote_markers(redir->file);
	if (!clean)
		return (1);
	free(redir->file);
	redir->file = clean;
	return (0);
}
