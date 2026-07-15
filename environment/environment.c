/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:24:01 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/15 17:23:46 by jefferson        ###   ########.fr       */
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
		return (0);
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
	return (1);
}