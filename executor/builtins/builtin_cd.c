/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:55:10 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/17 15:52:00 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

static int	update_cd_pwd(t_shell *shell, char *prev, char *curr, char *target)
{
	if (!getcwd(prev, PATH_MAX))
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(target))
	{
		cd_error(target);
		return (1);
	}
	if (!getcwd(curr, PATH_MAX))
	{
		perror("getcwd");
		return (1);
	}
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
	char	*value;
	char	*target;

	target = cmd->args[1];
	if (target == NULL)
	{
		value = get_env_value(shell->env, "HOME");
		if (!value)
			return (1);
		target = value;
	}
	else
	{
		if (cmd->args[2] != NULL)
		{
			error("cd", "too many arguments", 1);
			return (1);
		}
	}
	if (update_cd_pwd(shell, old_pwd, new_pwd, target))
		return (1);
	free(value);
	return (0);
}
