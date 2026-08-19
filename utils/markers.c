/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:32:07 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/19 14:15:43 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_whitespace(char c)
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

int		is_special_char(char c)
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

void	buffer_push(char *string, int *index, char c)
{
	string[*index] = c;
	(*index)++;
}

int		quote_state(char c)
{
	if (c == '\'')
		return (IN_SINGLE_QUOTE);
	return (IN_DOUBLE_QUOTE);
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