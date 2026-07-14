/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:51:23 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/04 12:51:23 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	minishell;
	
	(void)argc;
	(void)argv;
	if (init_shell(&minishell, envp))
		return (1);
	shell_loop(&minishell);
	return (0);
}

