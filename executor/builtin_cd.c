/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:55:10 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/13 15:10:28 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

int	ft_builtin_cd(t_cmd *cmd, t_shell *shell)
{
	(void) shell;
	if (cmd->args[1] == NULL)
	{
		ft_putstr_fd("cd: no arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	} 
	if (chdir(cmd->args[1]))
	{
		cd_error(cmd->args[1]);
		return (1);
	}
	return (0); 
}

