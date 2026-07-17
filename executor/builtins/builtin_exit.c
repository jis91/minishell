/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 10:21:13 by aganz             #+#    #+#             */
/*   Updated: 2026/07/15 10:21:13 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
		exit(shell->exit_status);
	else if (cmd->args[2] != NULL)
		return (error("exit", "too many arguments", 1));
	else if (!ft_isdigit(cmd->args[1][0]) && cmd->args[1][0] != '-')
	{
		error("exit", "numeric argument required", 255);
		exit(255);
	}
	else
		exit(ft_atoi(cmd->args[1]));
	return (0);
}
