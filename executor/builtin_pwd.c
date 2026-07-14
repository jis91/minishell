/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:04:13 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/13 13:26:51 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	size_t	size;
	char 	result[PATH_MAX];

	(void) shell;
	(void) cmd;
	if (!getcwd(result, PATH_MAX))
	{
		perror("pwd");
		return(1);
	}
	size = ft_strlen(result);
	write (STDOUT_FILENO, result, size);
	return (0);
}