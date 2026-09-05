/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 14:20:50 by aganz             #+#    #+#             */
/*   Updated: 2026/08/26 14:28:22 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_buffer(char *arg, int *index, t_shell *shell)
{
	char	*buffer;

	if (arg[*index] == QUOTE_MARKER && arg[(*index) + 1] == '$')
	{
		buffer = ft_strdup("$");
		(*index) += 2;
	}
	else if (arg[*index] == DQUOTE_MARKER && arg[(*index) + 1] == '$')
	{
		(*index) += 2;
		buffer = expand(arg, index, shell);
	}
	else if (arg[*index] == '$')
	{
		(*index)++;
		buffer = mark_splits(expand(arg, index, shell));
	}
	else if (arg[*index] == BOUNDARY_MARKER)
	{
		(*index)++;
		buffer = no_expand(arg, index);
	}
	else
		buffer = no_expand(arg, index);
	return (buffer);
}

char	*assembler(char *arg, t_shell *shell)
{
	char	*buffer;
	char	*tmp;
	char	*result;
	int		index;

	index = 0;
	result = ft_strdup("");
	if (!result)
		fatal_error(shell, NULL, "malloc failed", 1);
	while (arg[index])
	{
		buffer = build_buffer(arg, &index, shell);
		if (!buffer)
		{
			free(result);
			fatal_error(shell, NULL, "malloc failed", 1);
		}
		tmp = result;
		result = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (result);
}
