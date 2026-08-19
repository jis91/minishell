/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:19:00 by jefferson         #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/08/19 14:23:05 by jefferson        ###   ########.fr       */
=======
/*   Updated: 2026/08/13 12:33:52 by aganz            ###   ########.fr       */
>>>>>>> origin/Arthur
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_buffer(char *arg, int *index, t_shell *shell)
{
	char	*buffer;

	if (arg[*index] == QUOTE_MARKER && arg[(*index) + 1] == '$')
	{
		buffer = ft_strdup("$");
		(*index) += 2;
	}
	else if (arg[*index] == DQUOTE_MARKER && arg[(*index) + 1] == '$')
	{
		(*index) += 2;
		buffer = expand(arg, index, shell);
	}
	else if (arg[*index] == '$')
	{
		(*index)++;
		buffer = mark_splits(expand(arg, index, shell));
	}
	else if (arg[*index] == BOUNDARY_MARKER)
	{
		(*index)++;
		buffer = no_expand(arg, index);
	}
	else
		buffer = no_expand(arg, index);
	return (buffer);
}

<<<<<<< HEAD
char	*assembler(char *arg, t_shell *shell)
=======
static char	*assembler(char *arg, t_shell *shell)
>>>>>>> origin/Arthur
{
	char	*buffer;
	char	*tmp;
	char	*result;
	int		index;

	index = 0;
	result = ft_strdup("");
	if (!result)
		fatal_error(shell, NULL, "malloc failed", 1);
	while (arg[index])
	{
		buffer = build_buffer(arg, &index, shell);
		if (!buffer)
		{
			free(result);
			fatal_error(shell, NULL, "malloc failed", 1);
		}
		tmp = result;
		result = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (result);
}

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

// static void fill_tmp(t_cmd *cmd, t_shell *shell, char ***tmp, int i);
void	expand_one_cmd(t_cmd *cmd, t_shell *shell)
{
	int		i;
<<<<<<< HEAD
	int		total;
	char	***tmp;
	char	**new_args;
	char	*assembled;
=======
	char	*tmp;
	t_redir	*redir;
>>>>>>> origin/Arthur

	i = 0;
	total = 0;
	tmp = ft_calloc(sizeof(char **), (count_env_length(cmd->args) + 1));
	while (cmd->args[i])
	{
		if (has_dollar_boundary(cmd->args[i]))
		{
			assembled = assembler(cmd->args[i], shell);
			tmp[i] = ft_split(assembled, SPLIT_MARKER);
			if (!tmp[i])
				fatal_error(shell, NULL, "malloc failed", 1);
			if (!tmp[i][0])
			{
				free_char_tab(tmp[i]);
				tmp[i] = init_char_tab(1);
				tmp[i][0] = ft_strdup("");
			}
			free(assembled);
		}
		else
		{
			tmp[i] = init_char_tab(1);
			tmp[i][0] = ft_strdup(cmd->args[i]);
		}
		total += count_env_length(tmp[i]);
		i++;
	}
<<<<<<< HEAD
	new_args = init_char_tab(total);
	merge_args(new_args, tmp);
	free_char_tab(cmd->args);
	cmd->args = new_args;
}

void	expander(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		expand_one_cmd(current, shell);
		current = current->next;
	}
=======
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->file && has_dollar_boundary(redir->file))
		{
			tmp = assembler(redir->file, shell);
			if (!tmp)
				return (1);
			free(redir->file);
			redir->file = tmp;
		}
		redir = redir->next;
	}
	return (0);
>>>>>>> origin/Arthur
}
