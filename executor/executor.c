/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:26 by aganz             #+#    #+#             */
/*   Updated: 2026/07/21 22:28:05 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int	exec_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		status;

	path = find_path(cmd, shell);
	if (!path)
		return (127);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (-1);
	}
	if (pid == 0)
	{
		reset_child_signals();
		execve(path, cmd->args, shell->env);
		free (path);
		exit (127);
	}
	waitpid(pid, &status, 0);
	free (path);
	return (WEXITSTATUS(status));
}*/

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	reset_child_signals();
	if (apply_redirections(cmd, shell) == -1)
		exit(1);
	path = find_path(cmd, shell);
	if (!path)
		exit (127);
	execve(path, cmd->args, shell->env);
	perror(cmd->args[0]);
	free (path);
	exit (127);
}

int exec_builtin_with_redir(t_cmd *cmds, t_shell *shell, t_builtin builtin)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (1);
	if (apply_redirections(cmds, shell) == -1)
	{
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

/*int	executor(t_cmd *cmds, t_shell *shell)
{
	int			count;
	t_builtin	builtin;
	t_pipe_ctx	ctx;

	if (!cmds)
		return (1);
	count = count_cmds(cmds);
	if (count == 1)
	{
		builtin = check_builtin(cmds);
		if (builtin != NOT_BUILTIN)
			return (exec_builtin(cmds, shell, builtin));
		else
			return (exec_external(cmds, shell));
	}
	else
	{
		init_pipe_ctx(&ctx);
		return (exec_pipeline(cmds, &ctx, shell));
	}
	return (0);
}*/

int	executor(t_cmd *cmds, t_shell *shell)
{
	int			count;
	int			status;
	pid_t		pid;
	t_builtin	builtin;
	t_pipe_ctx	ctx;

	if (!cmds)
		return (1);
	count = count_cmds(cmds);
	if (count == 1)
	{
		builtin = check_builtin(cmds);
		if (builtin != NOT_BUILTIN)
			return (exec_builtin_with_redir(cmds, shell, builtin));
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			exec_external(cmds, shell);
		setup_exec_signals();
		waitpid(pid, &status, 0);
		setup_prompt_signals();
		return (WEXITSTATUS(status));
	}
	init_pipe_ctx(&ctx);
	return (exec_pipeline(cmds, &ctx, shell));
}

