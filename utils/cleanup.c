/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:35:29 by aganz             #+#    #+#             */
/*   Updated: 2026/08/02 21:47:32 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_cycle(t_token *tokens, t_cmd *cmd)
{
	free_tokens(tokens);
	free_cmds(cmd);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell || !shell->env)
		return ;
	free_char_tab(shell->env);
	shell->env = NULL;
}