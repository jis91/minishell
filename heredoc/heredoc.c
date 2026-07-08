#include "../minishell.h"

void	handle_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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
				if (read_one_heredoc(redir->file) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	read_one_heredoc(t_redir *redir)
{
	char	*line;
	int		fd[2];
	size_t	line_len;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (g_signal == SIGINT)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return (-1);
		}
		line_len = ft_strlen(line);
		if (line_len > 0 && line[line_len -1] == '\n')
			line_len--;
		if(!ft_strncmp(line, redir->file, line_len) && line_len == ft_strlen(redir->file))	
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	return (0);
}