/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 10:46:10 by aganz             #+#    #+#             */
/*   Updated: 2026/07/15 10:46:10 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	index;
	int	i;

	if (cmd->args[1] == NULL)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		index = find_env_index(shell->env, cmd->args[i]);
		if (index == -1)
		{
			i++;
			continue ;
		}
		free(shell->env[index]);
		while (shell->env[index + 1])
		{
			shell->env[index] = shell->env[index + 1];
			index++;
		}
		shell->env[index] = NULL;
		i++;
	}
	return (0);
}
