#include "../minishell.h"

void    handle_quotes(t_lexer *lexer)
{
    if ((lexer->input[lexer->i] == '\'' && lexer->state == IN_SINGLE_QUOTE)
        || (lexer->input[lexer->i] == '"' && lexer->state == IN_DOUBLE_QUOTE))
    {    
        lexer->state = NORMAL;
        lexer->i++;
    }
    else
    {
        lexer->buffer[lexer->buffer_index] = lexer->input[lexer->i];
        lexer->i++;
        lexer->buffer_index++;
    }
}

void    handle_normal(t_lexer *lexer)
{
    if ((lexer->input[lexer->i] == ' ') || (lexer->input[lexer->i] == '\t'))
    {
        if (lexer->buffer_index > 0)
            flush_buffer(lexer, TOKEN_WORD);
        lexer->i++;
    }
    else if (lexer->input[lexer->i] == '\'')
    {
        lexer->state = IN_SINGLE_QUOTE;
        lexer->i++;
    }
    else if (lexer->input[lexer->i] == '"')
    {
        lexer->state = IN_DOUBLE_QUOTE;
        lexer->i++;
    }
    else if (lexer->input[lexer->i] == '|'
            || lexer->input[lexer->i] == '<' 
            || lexer->input[lexer->i] == '>')
    {
        if (lexer->buffer_index > 0)
            flush_buffer(lexer, TOKEN_WORD);
        handle_operator(lexer);
    }
    else 
    {
        lexer->buffer[lexer->buffer_index] = lexer->input[lexer->i];
        lexer->buffer_index++;
        lexer->i++;
    }
}

void    handle_operator(t_lexer *lexer)
{
    if (lexer->input[lexer->i] == '|')
    {
        add_token(lexer, TOKEN_PIPE);
        lexer->i++;
    }
    else if (lexer->input[lexer->i] == '<')
    {
        if (lexer->input[lexer->i + 1] == '<')
        {
            add_token(lexer, TOKEN_HEREDOC);
            lexer->i += 2;
        }
        else
        {
            add_token(lexer, TOKEN_REDIR_IN);
            lexer->i++;
        }
    }
    else if (lexer->input[lexer->i] == '>')
    {
        if (lexer->input[lexer->i + 1] == '>')
        {
            add_token(lexer, TOKEN_REDIR_APP);
            lexer->i += 2;
        }
        else
        {
            add_token(lexer, TOKEN_REDIR_OUT);
            lexer->i++;
        }
    }
}

void    add_token(t_lexer *lexer, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        ft_printf("minishell: Malloc failed\n");
        free(lexer->buffer);
        return ;
    }
    token->value = NULL;
    token->type = type;
    token->next = NULL;
    if (lexer->head == NULL)
    {
        lexer->head = token;
        lexer->tail = token;
    }
    else 
    {
        lexer->tail->next = token;
        lexer->tail = token;
    }
}

void    flush_buffer(t_lexer *lexer, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        ft_printf("minishell: Malloc failed\n");
        free(lexer->buffer);
        return ;
    }
    lexer->buffer[lexer->buffer_index] = '\0';
    token->value = ft_strdup(lexer->buffer);
    token->type = type;
    token->next = NULL;
    if (lexer->head == NULL)
    {
        lexer->head = token;
        lexer->tail = token;
    }
    else 
    {
        lexer->tail->next = token;
        lexer->tail = token;
    }
    lexer->buffer_index = 0;
}