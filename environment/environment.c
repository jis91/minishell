/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:24:01 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/22 13:05:24 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_length(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
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

int	add_env_var(t_shell *shell, char *name, char *value)
{
	int		env_length;
	char	**new_shell_env;
	char	*tmp;
	int		i;

	i = 0;
	env_length = count_env_length(shell->env);
	new_shell_env = malloc(sizeof(char *) * (env_length + 2));
	if (!new_shell_env)
		return (1);
	while (shell->env[i])
	{
		new_shell_env[i] = shell->env[i];
		i++;
	}
	tmp = ft_strjoin(name, "=");
	new_shell_env[i] = ft_strjoin(tmp, value);
	free(tmp);
	i++;
	new_shell_env[i] = NULL;
	free(shell->env);
	shell->env = new_shell_env;
	return (0);
}

int	apply_to_env(t_shell *shell, char *name, char *value)
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
		if (add_env_var(shell, name, value))
			return (1);
	}
	return (0);
}

char	*get_env_value(char **env, char *name)
{
	int		index;
	int		name_length;
	int		envindex_length;
	char	*result;
	
	name_length = ft_strlen(name) + 1;
	index = find_env_index(env, name);
	if (index == -1)
		return (NULL);
	envindex_length = ft_strlen(env[index]);
	result = ft_substr(env[index], name_length, envindex_length - name_length);
	if (!result)
		fatal_error(NULL, "Malloc failed", 1);
	return (result);
}


