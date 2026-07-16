/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:19:15 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/16 10:47:27 by jefferson        ###   ########.fr       */
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

static int	verify_value(char *value, char *name)
{
	if (!value)
	{
		free(name);
		return (1);
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
		if (!*name)
			return (1);
		*value = ft_strdup(equals + 1);
		if (verify_value(*value, *name))
			return (1);
	}
	else
	{
		*name = ft_strdup(arg);
		if (!*name)
			return (1);
		*value = ft_strdup("");
		if (verify_value(*value, *name))
			return (1);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		exit_code;
	char	*name;
	char	*value;

	if (cmd->args[1] == NULL)
		return (builtin_env(shell));
	i = 1;
	exit_code = 0;
	while (cmd->args[i])
	{
		if (trim_arg_value(cmd->args[i], &value, &name))
		{
			exit_code = 1;
			break ;
		}
		if (legit_export_arguments(name) || apply_to_env(shell, name, value))
			exit_code = 1;
		free(name);
		free(value);
		i++;
	}
	return (exit_code);
}
