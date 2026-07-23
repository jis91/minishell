/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:56:57 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/22 13:04:26 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_var(char *arg, int *index, char **env)
{
	char	*name;
	char	*result;
	int		name_length;
	int		i;

	i = *index;
	while (arg[*index])
	{
		if (!is_valid_char_name(arg[*index], (*index) - i))
			break;
		(*index)++;
	}
	name_length = *index - i;
	name = malloc(sizeof(char) * (name_length + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, &arg[i], name_length + 1);
	result = get_env_value(env, name);
	if (!result)
		result = ft_strdup("");
	free(name);
	return (result);
}