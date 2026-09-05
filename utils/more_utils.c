/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 17:11:59 by jstrasse          #+#    #+#             */
/*   Updated: 2026/08/19 17:13:51 by jstrasse         ###   ########.fr       */
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

int	is_special_char(char c)
{
	if (c == QUOTE_MARKER)
		return (c);
	else if (c == DQUOTE_MARKER)
		return (c);
	else if (c == BOUNDARY_MARKER)
		return (c);
	else if (c == SPLIT_MARKER)
		return (c);
	else if (c == '$')
		return (DOLLAR_SIGN);
	else
		return (0);
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
