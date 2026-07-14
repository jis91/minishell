/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:19:15 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/14 16:04:00 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	
int	find_env_index(char **env, char *name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 &&
				env[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}