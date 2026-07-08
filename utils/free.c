/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:51:46 by aganz             #+#    #+#             */
/*   Updated: 2026/07/08 14:44:19 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
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
		free(redirections);
		redirections = tmp;
	}
}