/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/23 21:24:47 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*assembler(char *arg, t_shell *shell)
{
	int		index;

	index = 0;
	while(arg[index])
	{
		if (arg[index] == '$')
			dispatch(arg, &index, shell);
	}
	
}

static char	*dispatch(char *arg, int *index, t_shell *shell)
{
	if (arg[*index + 1] == '?')
	{
		expand_exit_status(arg, shell->exit_status);
		(*index)++;
		return (ft_itoa(shell->exit_status));
	}
	else if (is_valid_char_name(arg[*index + 1], 0))
		return (expand_var(arg, *index, shell->env));
	else
		return (ft_strdup("$")); 
}

int 	*expand_exit_status(char *arg, int exit_status);
