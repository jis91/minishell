/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/22 13:35:01 by jefferson        ###   ########.fr       */
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
char	*assembler(char *arg, t_shell *shell);
char	*dispatcher(char *arg, int index);
char	*expand_var(char *arg, int *index, char **env);
char 	*expand_exit_status(char *arg, int exit_status);
char	*no_expand(char *arg);











"$HOME"

if $
if $?
if $VAR
if $error 