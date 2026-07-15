/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:19:15 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/15 17:08:15 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	legit_export_arguments(char *name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return(0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	verify_value(char *value, char *name)
{
	if (!value)
	{
		free(name);
		return (0);
	}
	return (1);
}

static int	trim_arg_value(char *arg, char **value, char **name)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		*name = ft_substr(arg, 0, equals - arg);
		if (!*name)
			return (0);
		*value = ft_strdup(equals + 1);
		if (!verify_value(*value, *name)) 
			return (0);
	}
	else
	{
		*name = ft_strdup(arg);
		if (!*name)
			return (0);
		*value = ft_strdup("");
		if (!verify_value(*value, *name))
			return (0);
	}
	return (1);
}

static int	apply_to_env(t_shell *shell, char *name, char *value)
{
	int		idx;
	char	*tmp;
	char	*env;
	
	idx = find_env_index(shell->env, name);
	if (idx >= 0)
	{
		tmp = ft_strjoin(name, "=");
		env = ft_strjoin(tmp, value);
		free(tmp);
		free(shell->env[idx]);
		shell->env[idx] = env;
	}
	else
	{
		if(!add_env_var(shell, name, value))
			return (0);
	}
	return (1);
}

int		builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		exit_code;
	char 	*name;
	char	*value;

	if (cmd->args[1] == NULL)
		return (ft_builtin_env(shell));
	i = 1;
	exit_code = 1;
	while (cmd->args[i])
	{
		if(!trim_arg_value(cmd->args[i], &value, &name))
		{
			exit_code = 0;
			break;
		}
		if (!legit_export_arguments(name) || !apply_to_env(shell, name, value))
			exit_code = 0;
		free(name);
		free(value);
		i++;
	}
	return (exit_code);
}
