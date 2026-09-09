/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 11:50:11 by jstrasse          #+#    #+#             */
/*   Updated: 2026/09/09 12:21:48 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_cleanup(void)
{
	int		i;
	char	**read_content;

	i = 0;
	while (i < MAX_FD)
	{
		read_content = get_content_slot(i);
		if ((*read_content))
		{
			free((*read_content));
			(*read_content) = NULL;
		}
		i++;
	}
}

char	**get_content_slot(int fd)
{
	static char	*read_content[MAX_FD];

	return (&read_content[fd]);
}
