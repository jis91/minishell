/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 17:11:59 by jstrasse          #+#    #+#             */
/*   Updated: 2026/09/06 19:52:28 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

void	replace_whitespace(char *value, int *i, char *result, int *j)
{
	while (is_whitespace(value[*i]))
		(*i)++;
	result[*j] = SPLIT_MARKER;
	(*j)++;
}

void	buffer_push(char *string, int *index, char c)
{
	string[*index] = c;
	(*index)++;
}

int	quote_state(char c)
{
	if (c == '\'')
		return (IN_SINGLE_QUOTE);
	return (IN_DOUBLE_QUOTE);
}

int	count_env_length(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
