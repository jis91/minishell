/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:26 by aganz             #+#    #+#             */
/*   Updated: 2026/08/25 22:27:01 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin_with_redir(t_cmd *cmds, t_shell *shell, t_builtin builtin)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (1);
	if (apply_redirections(cmds) == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	result = exec_builtin(cmds, shell, builtin);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell, t_builtin builtin)
{
	if (builtin == BUILTIN_ECHO)
		return (builtin_echo(cmd));
	if (builtin == BUILTIN_CD)
		return (builtin_cd(cmd, shell));
	if (builtin == BUILTIN_PWD)
		return (builtin_pwd());
	if (builtin == BUILTIN_EXPORT)
		return (builtin_export(cmd, shell));
	if (builtin == BUILTIN_UNSET)
		return (builtin_unset(cmd, shell));
	if (builtin == BUILTIN_ENV)
		return (builtin_env(shell));
	if (builtin == BUILTIN_EXIT)
		return (builtin_exit(cmd, shell));
	return (0);
}

static int	execute_single(t_cmd *cmds, t_shell *shell)
{
	pid_t		pid;
	t_builtin	builtin;
	int			status;

	builtin = check_builtin(cmds);
	if (builtin != NOT_BUILTIN)
	{
		shell->exit_status
			= (exec_builtin_with_redir(cmds, shell, builtin));
		return (shell->exit_status);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		exec_external(cmds, shell);
		exit(1);
	}
	setup_exec_signals();
	waitpid(pid, &status, 0);
	setup_prompt_signals();
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
	return (get_exit_status(status));
}

int	executor(t_cmd *cmds, t_shell *shell)
{
	t_pipe_ctx	ctx;

	if (!cmds)
		return (1);
	if (count_cmds(cmds) == 1)
	{
		shell->exit_status = execute_single(cmds, shell);
		return (shell->exit_status);
	}
	init_pipe_ctx(&ctx);
	shell->exit_status = (exec_pipeline(cmds, &ctx, shell));
	return (shell->exit_status);
}
