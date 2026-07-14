/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 14:25:33 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/12 13:55:47 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *arg)
{
	int		i;

	i = 1;
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	parse_flag(t_cmd *cmd, int *i, int *flag)
{
	while (cmd->args[*i])
	{
		if (is_n_flag(cmd->args[*i]))
			*flag = 1;
		else
			break ;
		(*i)++;
	}
}

int	ft_builtin_echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		flag;
	int		first_word;

	(void) shell;
	i = 1;
	flag = 0;
	first_word = 1;
	parse_flag(cmd, &i, &flag);
	while (cmd->args[i])
	{
		if (!first_word)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		first_word = 0;
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
