/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:51:52 by jefferson         #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/08/05 19:12:40 by jefferson        ###   ########.fr       */
=======
/*   Updated: 2026/08/03 23:09:27 by aganz            ###   ########.fr       */
>>>>>>> 35b10cd112b3e5d2a005095873c529a88b94a271
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

/*void	fatal_error(char *context, char *msg, int code)
{
	error(context, msg, code);
	exit(code);
}*/

void	fatal_error(t_shell *shell, char *context, char *msg, int code)
{
	error(context, msg, code);
	if (shell)
		cleanup_shell(shell);
	exit(code);
}
