/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:58:03 by aganz             #+#    #+#             */
/*   Updated: 2026/07/31 14:58:03 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	compare_by_name(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] == '\0' || s1[i] == '=') && (s2[i] == '\0' || s2[i] == '='))
			return (0);
		if ((s1[i] == '\0' || s1[i] == '=') && s2[i])
			return (-1);
		else if ((s2[i] == '\0' || s2[i] == '=') && s1[i])
			return (1);
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void	sort_char_tab(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i + 1])
	{
		if (compare_by_name(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

char	**init_char_tab(int length)
{
	char	**result;

	result = ft_calloc(sizeof(char *), (length + 1));
	if (!result)
		fatal_error(NULL, NULL, "malloc failed", 1);
	return (result);
}
