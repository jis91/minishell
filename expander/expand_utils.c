/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 08:27:51 by jefferson         #+#    #+#             */
/*   Updated: 2026/07/21 14:28:12 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_valid_char_name(char c, int position)
{
	if (position == 0)
	{
		if (!ft_isalpha(c) && c != '_')
			return (0);
	}
	else
	{
		if (!ft_isalnum(c) && c != '_')
			return (0);
	}
	return (1);	
}