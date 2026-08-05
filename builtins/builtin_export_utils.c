/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:57:55 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/05 19:41:12 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_result(char **names, char **values)
{
	int	i;

	i = 0;
	while (names[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(names[i], STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(values[i], STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		i++;
	}
}

static void	build_names_values(char **tmp_env, char **names, char **values)
{
	int	i;

	i = 0;
	while (tmp_env[i])
	{
		trim_arg_value(tmp_env[i], &values[i], &names[i]);
		i++;
	}
}

static void	build_tmp_env(char **env, char **tmp_env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
			fatal_error(NULL, NULL, "malloc failed", 1);
		i++;
	}
	sort_char_tab(tmp_env);
}

void	print_export_no_arg(char **env)
{
	char	**names;
	char	**values;
	char	**tmp_env;
	int		env_length;

	env_length = count_env_length(env);
	names = init_char_tab(env_length);
	values = init_char_tab(env_length);
	tmp_env = init_char_tab(env_length);
	build_tmp_env(env, tmp_env);
	build_names_values(tmp_env, names, values);
	print_result(names, values);
	free_char_tab(names);
	free_char_tab(values);
	free_char_tab(tmp_env);
}
