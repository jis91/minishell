/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 08:58:12 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/14 11:45:36 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_fd(int *fd_write, int *fd_read)
{
	*fd_write = open("/tmp/.minishell_heredoc", O_CREAT
			| O_RDWR | O_TRUNC, 0600);
	*fd_read = open("/tmp/.minishell_heredoc", O_RDONLY);
	unlink("/tmp/.minishell_heredoc");
	if (*fd_write == -1 || *fd_read == -1)
	{
		if (*fd_write != -1)
			close(*fd_write);
		if (*fd_read != -1)
			close(*fd_read);
		return (-1);
	}
	return (0);
}

static int	compare_line_to_redir(char *line, t_redir *redir)
{
	size_t	line_length;

	line_length = ft_strlen(line);
	if (line_length > 0 && line[line_length -1] == '\n')
		line_length--;
	if (!ft_strncmp(line, redir->file, line_length)
		&& line_length == ft_strlen(redir->file))
		return (1);
	return (0);
}

static int	check_heredoc_signal(char *line, int fd_write, int fd_read)
{
	if (g_signal == SIGINT)
	{
		free(line);
		g_signal = 0;
		close(fd_write);
		close(fd_read);
		return (-1);
	}
	return (0);
}

static int	read_one_heredoc(t_redir *redir)
{
	char	*line;
	int		fd_write;
	int		fd_read;

	if (open_fd(&fd_write, &fd_read))
		return (-1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (check_heredoc_signal(line, fd_write, fd_read))
			return (-1);
		if (compare_line_to_redir(line, redir))
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	close(fd_write);
	redir->heredoc_fd = fd_read;
	return (0);
}

int	collect_heredoc(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	setup_heredoc_signals();
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				if (read_one_heredoc(redir) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
