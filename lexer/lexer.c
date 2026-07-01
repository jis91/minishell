#include "../minishell.h"

static void    init_lexer (t_lexer *lexer, char *input)
{
    lexer->input = input;
    lexer->buffer = malloc(ft_strlen(input) + 1);
    lexer->state = NORMAL;
    lexer->i = 0;
    lexer->buffer_index = 0;
    lexer->head = NULL;
    lexer->tail = NULL;
}

t_token *lexer(char *input)
{
    t_lexer     lexer;

    init_lexer(&lexer, input);
    while(lexer.input[lexer.i] != '\0')
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
