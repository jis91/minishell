/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
/*   Updated: 2026/09/01 22:09:27 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	merge_args(char **new_args, char ***tmp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			new_args[k] = tmp[i][j];
			k++;
			j++;
		}
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

static char	**expand_arg(char *arg, t_shell *shell)
{
	char	**result;
	char	*assembled;

	if (!has_dollar_boundary(arg))
	{
		result = init_char_tab(1);
		result[0] = ft_strdup(arg);
		return (result);
	}
	assembled = assembler(arg, shell);
	result = ft_split(assembled, SPLIT_MARKER);
	free(assembled);
	if (!result)
		fatal_error(shell, NULL, "malloc failed", 1);
	if (!result[0])
	{
		free_char_tab(result);
		if(contains_marker(arg))
		{
			result = init_char_tab(1);
			result[0] = ft_strdup("");
		}
		else
			result = init_char_tab(0);
	}
	return (result);
}

void	expand_one_cmd(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		total;
	char	***tmp;
	char	**new_args;

	i = 0;
	total = 0;
	tmp = ft_calloc(sizeof(char **), (count_env_length(cmd->args) + 1));
	while (cmd->args[i])
	{
		tmp[i] = expand_arg(cmd->args[i], shell);
		total += count_env_length(tmp[i]);
		i++;
	}
	new_args = init_char_tab(total);
	merge_args(new_args, tmp);
	free_char_tab(cmd->args);
	cmd->args = new_args;
}

void	expander(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;
	t_redir	*redir;
	char	*tmp;

	current = cmd;
	while (current)
	{
		expand_one_cmd(current, shell);
		redir = current->redirections;
		while (redir)
		{
			if (redir->file && has_dollar_boundary(redir->file))
			{
				tmp = assembler(redir->file, shell);
				if (!tmp)
					fatal_error(shell, NULL, "malloc failed", 1);
				free(redir->file);
				redir->file = tmp;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
