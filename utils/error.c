/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:51:52 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/16 17:50:17 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	syntax_error(void)
{
	ft_printf("minishell: syntax error near unexpected token\n");
	return (1);
}

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

void	fatal_error(char *context, char *msg, int code)
{
	error(context, msg, code);
	exit(code);
}
