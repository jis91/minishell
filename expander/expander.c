/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/25 13:29:44 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_result(char *result, char *buffer)
{
	char *tmp;
	
	tmp = result;
	result = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (result);
}

static char	*assembler(char *arg, t_shell *shell)
{
	int		index;
	char	*buffer;
	char	*result;

	index = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while(arg[index])
	{
		if (arg[index] == '$')
		{
			index++;
			buffer = expand(arg, &index, shell);
		}
		else
			buffer = no_expand(arg, &index);
		if (!buffer)
		{
			free(result);
			return (NULL);
		}
		result = build_result(result, buffer);
	}
	return (result);
}

static int		has_dollar(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int		expander(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*tmp;
	i = 0;
	while (cmd->args[i])
	{
		if (has_dollar(cmd->args[i]))
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


