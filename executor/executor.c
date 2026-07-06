/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:26 by aganz             #+#    #+#             */
/*   Updated: 2026/07/06 23:35:43 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_external(t_cmd *cmds, t_shell *shell)
{

}

int	ft_executor(t_cmd *cmds, t_shell *shell)
{
	t_cmd		*current;
	int			count;
	t_builtin	builtin;

	count = ft_count_cmds(cmds);
	current = cmds;
	if (!cmds)
		return (1);
		builtin = ft_check_builtin(cmds);
	if (count == 1)
	{
		if (builtin != NOT_BUILTIN)
			ft_exec_builtin()
		else
			ft_exec_external()
	}
	else
	{
		while (current)
		// code
		current = current->next;
	}
}
