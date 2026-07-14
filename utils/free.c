/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:51:46 by aganz             #+#    #+#             */
/*   Updated: 2026/07/14 12:04:33 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_int_tab(int **tab, int	size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->args);
		free_redirs(cmd->redirections);
		free(cmd);
		cmd = tmp;
	}
}

void	free_redirs(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections)
	{
		tmp = redirections->next;
		if (redirections->heredoc_fd != -1)
			close(redirections->heredoc_fd);
		free(redirections);
		redirections = tmp;
	}
}

void cleanup_cycle(t_token *tokens, t_cmd *cmd)
{
    free_tokens(tokens);
    free_cmds(cmd);
}