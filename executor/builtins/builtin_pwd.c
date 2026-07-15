/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:04:13 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/15 23:02:38 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(void)
{
	size_t	size;
	char	result[PATH_MAX];

	if (!getcwd(result, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	size = ft_strlen(result);
	write(STDOUT_FILENO, result, size);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
