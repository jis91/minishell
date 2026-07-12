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

static char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOKEN_REDIR_APP)
		return ("REDIR_APP");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

static void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_redir	*redir_tmp;
	int		i;

	tmp = cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			ft_printf("%s\n", tmp->args[i]);
			i++;
		}
		redir_tmp = tmp->redirections;
		while (redir_tmp)
		{
			ft_printf("%s, %s\n",
				token_type_str(redir_tmp->type), redir_tmp->file);
			redir_tmp = redir_tmp->next;
		}
		tmp = tmp->next;
	}
}

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

