/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:51:46 by aganz             #+#    #+#             */
/*   Updated: 2026/07/10 14:27:05 by aganz            ###   ########.fr       */
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