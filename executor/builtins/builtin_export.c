/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:19:15 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/17 13:23:34 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	legit_export_arguments(char *name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	trim_arg_value(char *arg, char **value, char **name)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		*name = ft_substr(arg, 0, equals - arg);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*name = ft_strdup(arg);
		*value = ft_strdup("");
	}
	if (!*name || !*value)
	{
		free(*name);
		free(*value);
		return (1);
	}
	return (0);
}

static int	print_export_no_arg(char **env)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (trim_arg_value(env[i], &value, &name))
			return (1);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		free(name);
		free(value);
		i++;
	}
	return (0);
}

static int	should_apply_export(char *arg, char *name, char **env)
{
	if (ft_strchr(arg, '='))
		return (1);
	if (find_env_index(env, name) == -1)
		return (1);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		exit_code;
	char	*name;
	char	*value;

	if (cmd->args[1] == NULL)
		return (print_export_no_arg(shell->env));
	i = 1;
	exit_code = 0;
	while (cmd->args[i])
	{
		if (trim_arg_value(cmd->args[i], &value, &name))
		{
			exit_code = 1;
			break ;
		}
		if (legit_export_arguments(name))
			exit_code = 1;
		else if (should_apply_export(cmd->args[i], name, shell->env)
				&& apply_to_env(shell, name, value))
			exit_code = 1;
		free(name);
		free(value);
		i++;
	}
	return (exit_code);
}
