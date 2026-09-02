/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:32:07 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/19 17:13:43 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mark_splits(char *value)
{
	int		i;
	int		j;
	char	*result;

	result = ft_calloc(sizeof(char), (ft_strlen(value) * 2) + 1);
	i = 0;
	j = 0;
	if (!result)
		fatal_error(NULL, NULL, "malloc failed", 2);
	while (value[i])
	{
		if (is_whitespace(value[i]))
			replace_whitespace(value, &i, result, &j);
		else
		{
			result[j] = value[i];
			j++;
			i++;
		}
	}
	free(value);
	return (result);
}

int	contains_marker(char *str)
{
	int	i;
	int	code;

	i = 0;
	while (str[i])
	{
		code = is_special_char(str[i]);
		if (code == QUOTE_MARKER || code == DQUOTE_MARKER
			|| code == BOUNDARY_MARKER)
			return (1);
		i++;
	}
	return (0);
}

int	has_dollar_boundary(char *string)
{
	int		i;
	int		code;

	i = 0;
	while (string[i])
	{
		code = is_special_char(string[i]);
		if (code == DOLLAR_SIGN || code == BOUNDARY_MARKER)
			return (1);
		i++;
	}
	return (0);
}

char	*strip_quote_markers(char *arg)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] != QUOTE_MARKER && arg[i] != DQUOTE_MARKER
			&& arg[i] != BOUNDARY_MARKER)
			result[j++] = arg[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
