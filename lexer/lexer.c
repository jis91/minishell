/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:01:56 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/04 12:01:56 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->state = NORMAL;
	lexer->i = 0;
	lexer->buffer_index = 0;
	lexer->head = NULL;
	lexer->tail = NULL;
	lexer->buffer = malloc(ft_strlen(input) + 1);
	if (!lexer->buffer)
		return (0);
	return (1);
}

t_token	*lexer(char *input)
{
	t_lexer	lexer;

	if (!init_lexer(&lexer, input))
	{
		ft_printf("malloc lexer failed\n");
		return (NULL);
	}
	while (lexer.input[lexer.i] != '\0')
	{
		if (lexer.state == NORMAL)
			handle_normal(&lexer);
		else
			handle_quotes(&lexer);
	}
	if (lexer.state != NORMAL)
	{
		ft_printf("minishell: unclosed quote\n");
		free(lexer.buffer);
		return (NULL);
	}
	if (lexer.buffer_index > 0)
		flush_buffer(&lexer, TOKEN_WORD);
	free(lexer.buffer);
	return (lexer.head);
}
