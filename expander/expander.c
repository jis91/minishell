/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/10 15:04:03 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_result(char *result, char *buffer)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (result);
}

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
		buffer = expand(arg, index, shell);
	}
	else if (arg[*index] == BOUNDARY)
	{
		(*index)++;
		buffer = no_expand(arg, index);
	}
	else
		buffer = no_expand(arg, index);
	return (buffer);	
}
static char	*assembler(char *arg, t_shell *shell)
{
	char	*buffer;
	char	*result;
	int		index;

	index = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (arg[index])
	{
		buffer = build_buffer(arg, &index, shell);
		if (!buffer)
		{
			free(result);
			return (NULL);
		}
		result = build_result(result, buffer);
	}
	return (result);
}

static int	has_dollar_boundary(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$' || string[i] == BOUNDARY)
			return (1);
		i++;
	}
	return (0);
}

int	expander(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		if (has_dollar_boundary(cmd->args[i]))
		{
			tmp = assembler(cmd->args[i], shell);
			if (!tmp)
				return (1);
			free(cmd->args[i]);
			cmd->args[i] = tmp;
		}
		i++;
	}
	return (0);
}
