README.MD
¨
https://github.com/42school/norminette/blob/master/pdf/fr.norm.pdf

https://www.youtube.com/watch?v=xCySbqj9BKI&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=1



LEXER :
PLAIN ENGLISH EXPLANATION : Separates the input into tokens :

TOKEN_WORD, TOKEN_PIPE '|' , TOKEN_REDIR_IN '<' , TOKEN_REDIR_OUT '>', TOKEN_REDIR_APP '>>', TOKEN_HEREDOC '<<'

lexer()           → main function, walks input string, returns token list
init_lexer()      → initializes the t_lexer struct (buffer, state, indexes)
handle_normal()   → handles current char when state is NORMAL
handle_quotes()   → handles current char when state is IN_SINGLE or IN_DOUBLE quote
handle_operator() → detects |, <, >, <<, >> and emits the right token
flush_buffer()    → turns accumulated buffer content into a TOKEN_WORD and appends it
add_token()       → creates a token of given type with NULL value and appends it
free_tokens()     → frees the entire token list


PARSER : 
PLAIN ENGLISH EXPLANATION : count total tokens, allocate arguments array based on count, create first command (t_cmd).
walk token list:
    TOKEN_WORD   → add to current t_cmd's char **args
    TOKEN_REDIR  → validate next token, create t_redir, attach to current cmd
    TOKEN_PIPE   → validate (not first, not last, not double)
                   finalize current cmd, create new one
end of list      → finalize last cmd

return cmd list head

parser()          → main function, walks token list, returns cmd list
parse_cmd()       → builds one t_cmd until PIPE or end of list
parse_args()      → collects WORD tokens into args array
parse_redir()     → consumes REDIR + next WORD into a t_redir node
syntax_error()    → prints error, returns NULL
free_cmds()       → frees the entire command list


HOW DOES MINISHELL WORK ?

LEXER TAKES INPUT AND GIVES A FLAT TOKEN LIST.
PARSER TAKES THE TOKEN LIST AND GIVES A LINKED LIST OF T_CMD STRUCTS. EACH NODE IS A CMD THAT TAKES ARGS AND REDIRECTIONS.