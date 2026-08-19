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

#include "../minishell.h"

int	apply_single_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_IN)
	{
		if (apply_redir_in(redir) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_REDIR_OUT)
	{
		if (apply_redir_out(redir) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_REDIR_APP)
	{
		if (apply_redir_append(redir) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		if (apply_redir_heredoc(redir) == -1)
			return (-1);
	}
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (apply_single_redir(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
