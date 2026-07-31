/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:22:32 by aganz             #+#    #+#             */
/*   Updated: 2026/07/31 16:53:54 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}

t_builtin	check_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NOT_BUILTIN);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (BUILTIN_UNSET);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (BUILTIN_EXIT);
	return (NOT_BUILTIN);
}

char	*verify_path(char **directories, t_cmd *cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (directories[i])
	{
		tmp = ft_strjoin(directories[i], "/");
		path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_in_path(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**directories;
	char	*path;

	i = 0;
	directories = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			directories = ft_split(shell->env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!directories)
	{
		error(cmd->args[0], "command not found", 127);
		return (NULL);
	}
	path = verify_path(directories, cmd);
	free_char_tab(directories);
	return (path);
}

char	*find_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->args[0][0] == '/'
			|| (cmd->args[0][0] == '.' && cmd->args[0][1] == '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (ft_strdup(cmd->args[0]));
		error(cmd->args[0], "command not found", 127);
		return (NULL);
	}
	path = find_in_path(cmd, shell);
	if (!path)
		error(cmd->args[0], "command not found", 127);
	return (path);
}

/*char	*find_path(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**directories;
	char	*path;

	if (cmd->args[0][0] == '/'
			|| (cmd->args[0][0] == '.' && cmd->args[0][1] == '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (ft_strdup(cmd->args[0]));
		error(cmd->args[0], "command not found", 127);
		return (NULL);
	}
	i = 0;
	directories = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			directories = ft_split(shell->env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!directories)
	{
		error(cmd->args[0], "command not found", 127);
		return (NULL);
	}
	path = verify_path(directories, cmd);
	free_char_tab(directories);
	if (!path)
		error(cmd->args[0], "command not found", 127);
	return (path);
}*/