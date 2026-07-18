/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 08:27:51 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/18 08:34:16 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		has_dollar(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
			return (1);
		i++;
	}
	return (0);
}