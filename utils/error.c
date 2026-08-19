/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 19:40:01 by jefferson         #+#    #+#             */
/*   Updated: 2026/08/13 13:48:51 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(char *context, char *msg, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd(context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	return (code);
}

void	fatal_error(t_shell *shell, char *context, char *msg, int code)
{
	error(context, msg, code);
	if (shell)
		cleanup_shell(shell);
	exit(code);
}
