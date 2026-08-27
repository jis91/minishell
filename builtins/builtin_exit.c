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

#include "../minishell.h"

static int	is_digit_flag(char *arg)
{
	int		i;

	i = 0;
	if ((arg[0] == '-' || arg[0] == '+')
		&& (!ft_isdigit(arg[1]) || arg[1] == '\0'))
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (arg[0] == '\0')
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_digit_flag(cmd->args[1]))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		shell->should_exit = 1;
		shell->exit_status = 2;
		return (2);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	shell->should_exit = 1;
	shell->exit_status = ft_atoi(cmd->args[1]);
	return (ft_atoi(cmd->args[1]));
}

/*int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
	{
		cleanup_shell(shell);
		exit(shell->exit_status);
	}
	if (!is_digit_flag(cmd->args[1]))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		cleanup_shell(shell);
		exit (2);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	cleanup_shell(shell);
	exit(ft_atoi(cmd->args[1]));
}*/