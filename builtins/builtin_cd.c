/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:55:10 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/03 08:51:46 by jefferson        ###   ########.fr       */
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

static int	update_cd_pwd(t_shell *shell, char *prev, char *curr, char *target)
{
	if (!getcwd(prev, PATH_MAX))
		return (1);
	if (chdir(target))
	{
		cd_error(target);
		return (1);
	}
	if (!getcwd(curr, PATH_MAX))
		return (1);
	if (apply_to_env(shell, "OLDPWD", prev))
		return (1);
	if (apply_to_env(shell, "PWD", curr))
		return (1);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*target;

	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (2);
	}
	target = cmd->args[1];
	if (!target)
		target = get_env_value(shell->env, "HOME");
	if (!target)
		return (1);
	if (update_cd_pwd(shell, old_pwd, new_pwd, target))
	{
		if (target != cmd->args[1])
			free(target);
		return (1);
	}
	if (target != cmd->args[1])
		free (target);
	return (0);
}
