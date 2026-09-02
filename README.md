*This project has been created as part of the 42 curriculum by jstrasse, aganz*

# Minishell

## Description
Minishell is the first group project in the 42 curriculum. The goal is to create a basic shell program in C based on Bash. It implements redirections and pipes, as well as envirionment variable expansions and the cd, echo, env, exit, export, pwd and unset builtin commands.

### How does Minishell work?
Minishell has 5 different steps:

1. **Lexer**
- reads the input line character by character
- separates the input into tokens (words, operations, redirections)
- handles single quotes, double quotes and special characters

Tokens: TOKEN_WORD, TOKEN_PIPE, TOKEN_REDIR_IN, TOKEN_REDIR_OUT, TOKEN_REDIR_APP, TOKEN_HEREDOC

2. **Parser**
- organize tokens into command structures (t_cmd)
- each command contains its arguments and redirections
- builds a linked list of commands for pipelines

3. **Heredoc**
- reads heredoc input before execution
- handles variable extension inside heredocs (unless delimiter is between quotes)

4. **Expander**
- expands environment varibles ($VAR, $?)
- removes quote markers left by the lexer
- handles word splitting for unquoted expansions

5. **Executor**
- handles single commands and pipelines
- applies redirections (stdin, stdout, append, heredoc)
- forks child processes for pipelines
- executes builtins directly in the parent process

**Features**
- **builtins**: echo (with option -n), cd, pwd, export, unset, env, exit
- **redirections**: <, >, <<, >>
- **pipes**: |
- **environment variables**: $VAR, $?
- **quotes**: single ('') and double ("")
- **signals**: ctrl-C, ctrl-D, ctrl-\

## Instructions
### Compilation
```bash
make        # compiles minishell
make clean  # cleans object files
make fclean # cleans object files and executables
- count total tokens
- allocate arguments array based on count
- create first command
make re     # full recompilation
```

### Execution
Run the program as you would run commands in any shell.
```bash
./minishell
minishell>
```

## Resources
- [CS 134 OS—4.1 Shell](https://www.youtube.com/watch?v=xCySbqj9BKI&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=1)
- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Building a Shell](https://healeycodes.com/building-a-shell)
- [Bash Tutorial](https://www.w3schools.com/bash/)
- [Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Chapter 5. Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [A Beginner’s Guide To Unix Shell Scripting](https://www.testmuai.com/blog/unix-shell-scripting/)
- [Introduction To Unix Signals Programming](https://www.cs.kent.edu/~ruttan/sysprog/lectures/signals.html)
- [Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
- [Understanding Unix Signals](https://www.youtube.com/watch?v=WxCwzcbZrJw&pp=ygUMdW5peCBzaWduYWxz)
- [minishell_tester](https://github.com/LucasKuhn/minishell_tester)
- [42_minishell_tester] (https://github.com/zstenger93/42_minishell_tester)

### AI Usage
AI tools were used as a learning and support tool during the project. They were used to rephrase and understand concepts such as lexer, heredoc, expander, executor and signals.
At the end, AI was used to help generate edge case tests.




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


right after fork(), in the child, before execve(), you need to reset SIGINT/SIGQUIT back to SIG_DFL.

Approach Chosenn : read loop in the parent (no fork just one pipe)

SIG_ATOMIC_T :

It's about what happens if a handler fires while the main code is mid-write to that variable.
Concretely: without an atomicity guarantee, on some architectures, writing a multi-byte value
could theoretically be interrupted after only some of the bytes have changed — so a handler
reading it right then would see a half-old, half-new garbage value. sig_atomic_t guarantees that
can't happen for that one variable.

VOLATILE :

without volatile (int instead for example) the variable wouldn't be read again at each iteration
of the loop but only after the loop. but we want a fresh read memory.
If not volatile this loop would be infinite. handler() changes the value of signal_g.

volatile sig_atomic_t signal_g = 0;

while (signal_g == 0)
	handler();

Ctrl-C : Generates SIGINT
Ctrl-\ : Generates SIGQUIT
Ctrl-D : Signals end-of-file on the input stream — no signal at all

 both signals reset to default in the child (symmetric), and at the prompt,
 SIGQUIT is ignored while SIGINT gets a real handler (asymmetric)

SIGQUIT :
Ctrl - /
signal(SIGQUIT, SIG_DFL)

Once a foreground child is running — you've launched cat, sleep 100, whatever — SIGQUIT needs
to go back to its real, default, terminate-and-dump behavior for that child, which is exactly
why the child resets it with signal(SIGQUIT, SIG_DFL) right after fork(), before execve().
Try Ctrl-\ on cat sometime: it dies immediately and prints Quit (core dumped) — that message
comes from your shell detecting the child died via that specific signal and reporting it, not
from the child itself printing anything (a killed process doesn't get to print a farewell message).

SIGINT :
Ctrl - C
sigaction(SIGINT, &sa, NULL);


After waitpid(), before setting shell->exit_status: check WIFSIGNALED(status). If true, exit_status
should be 128 + WTERMSIG(status) instead of WEXITSTATUS(status). Also, if the signal is SIGQUIT,
print Quit (core dumped) to stderr — matches bash's behavior for Ctrl-\ during a foreground command.
SIGINT should print nothing extra.

