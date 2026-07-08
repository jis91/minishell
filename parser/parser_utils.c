/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:19:29 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/04 12:19:29 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_token **tokens, t_cmd **current, int *i, int total_token)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		(*current)->args[*i] = (*tokens)->value;
		(*i)++;
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		(*current)->args[*i] = NULL;
		*i = 0;
		if (validate_cmd(*current))
			return (1);
		(*current)->next = init_cmd(total_token);
		(*current) = (*current)->next;
		*tokens = (*tokens)->next;
	}
	else
	{
		if (parse_redir(tokens, (*current)))
			return (1);
	}
	return (0);
}

int	parse_redir(t_token **tokens, t_cmd *current)
{
	t_redir	*new_redir;
	t_redir	**tmp;

	tmp = &current->redirections;
	if ((*tokens)->next && (*tokens)->next->type == TOKEN_WORD)
	{
		new_redir = malloc(sizeof(t_redir));
		if (!new_redir)
			return (1);
		new_redir->next = NULL;
		new_redir->type = (*tokens)->type;
		new_redir->file = (*tokens)->next->value;
		new_redir->heredoc_fd = -1;
		while (*tmp)
			tmp = &(*tmp)->next;
		*tmp = new_redir;
		(*tokens) = (*tokens)->next;
		(*tokens) = (*tokens)->next;
	}
	else
		return (syntax_error());
	return (0);
}
