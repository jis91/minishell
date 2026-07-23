/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:18:01 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/04 12:18:01 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parser(t_token *tokens)
{
	int		total_token;
	int		i;
	t_cmd	*current;
	t_cmd	*head;
	t_token	*cursor;

	if (!tokens)
		return (NULL);
	i = 0;
	cursor = tokens;
	total_token = count_token(tokens);
	head = init_cmd(total_token);
	current = head;
	while (cursor)
	{
		if (parse_token(&cursor, &current, &i, total_token))
			return (cleanup_parser(head, tokens));
	}
	current->args[i] = NULL;
	if (validate_cmd(current) == 1)
		return (cleanup_parser(head, tokens));
	return (head);
}

int	count_token(t_token *tokens)
{
	int	result;

	result = 0;
	while (tokens)
	{
		result++;
		tokens = tokens->next;
	}
	return (result);
}

t_cmd	*init_cmd(int total_token)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->args = malloc(sizeof(char *) * (total_token + 1));
	if (!command->args)
	{
		free(command);
		return (NULL);
	}
	command->redirections = NULL;
	command->next = NULL;
	return (command);
}

int	validate_cmd(t_cmd *current)
{
	if (current->args[0] == NULL)
		return (error(NULL, "syntax error near unexpected token", 2));
	return (0);
}

t_cmd	*cleanup_parser(t_cmd *head, t_token *tokens)
{
	free_cmds(head);
	free_tokens(tokens);
	return (NULL);
}
