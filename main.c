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

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmds;

	if (argc != 2)
		return (1);
	tokens = lexer(argv[1]);
	current = tokens;
	while (current)
	{
		ft_printf("[%s] : %s\n", token_type_str(current->type), current->value);
		current = current->next;
	}
	cmds = parser(tokens);
	if (!cmds)
		return (1);
	print_cmds(cmds);
	free_cmds(cmds);
	free_tokens(tokens);
	return (0);
}
