/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:04:54 by aganz             #+#    #+#             */
/*   Updated: 2026/08/25 22:28:12 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_absolute_path(t_cmd *cmd)
{
	int	saved_errno;

	if (access(cmd->args[0], X_OK) == 0)
		return (ft_strdup(cmd->args[0]));
	saved_errno = errno;
	if (saved_errno == EACCES || saved_errno == EISDIR)
		error(cmd->args[0], "Permission denied", 126);
	else
		error(cmd->args[0], "command not found", 127);
	errno = saved_errno;
	return (NULL);
}

char	*handle_dot(void)
{
	error(".", "filename argument required", 2);
	errno = EINVAL;
	return (NULL);
}

char	*handle_dot_dot(void)
{
	error("..", "command not found", 127);
	errno = ENOENT;
	return (NULL);
}

char	*handle_tilde(t_cmd *cmd)
{
	error(cmd->args[0], "Is a directory", 126);
	errno = EISDIR;
	return (NULL);
}
