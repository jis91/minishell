/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 08:27:51 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/02 20:57:08 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_char_name(char c, int position)
{
	if (position == 0)
	{
		if (!ft_isalpha(c) && c != '_')
			return (0);
	}
	else
	{
		if (!ft_isalnum(c) && c != '_')
			return (0);
	}
	return (1);
}

static char	*expand_var(char *arg, int *index, char **env)
{
	char	*name;
	char	*result;
	int		name_length;
	int		i;

	i = *index;
	while (arg[*index])
	{
		if (!is_valid_char_name(arg[*index], (*index) - i))
			break ;
		(*index)++;
	}
	name_length = *index - i;
	name = malloc(sizeof(char) * (name_length + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, &arg[i], name_length + 1);
	result = get_env_value(env, name);
	if (!result)
		result = ft_strdup("");
	free(name);
	return (result);
}

char	*expand(char *arg, int *index, t_shell *shell)
{
	if (arg[*index] == '?')
	{
		(*index)++;
		return (ft_itoa(shell->exit_status));
	}
	else if (is_valid_char_name(arg[*index], 0))
		return (expand_var(arg, index, shell->env));
	else
		return (ft_strdup("$"));
}

char	*no_expand(char *arg, int *index)
{
	char	*result;
	int		i;

	i = *index;
	while (arg[*index])
	{
		if (arg[*index] == '$' || arg[*index] == QUOTE_MARKER)
			break ;
		(*index)++;
	}
	result = malloc(sizeof(char) * ((*index) - i + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &arg[i], (*index) - i + 1);
	return (result);
}
