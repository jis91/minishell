/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:46:50 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:36:02 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <strings.h> /* Necessary to try the real bzero*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *) s;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	buffer[20] = "Hello World";
	char	buffer1[20] = "This is Bzero";

	printf("buffer before bzero : %s, %ld is length\n",
	 buffer, ft_strlen(buffer));
	printf("buffer1 before ft_bzero:  %s, %ld is length\n",
	 buffer1, ft_strlen(buffer1));
	bzero(buffer, 4);
	ft_bzero(buffer1, 5);
	printf("buffer after bzero : %s, %ld is length\n",
	 buffer, ft_strlen(buffer));
	printf("buffer1 after ft_bzero: %s, %ld is length\n",
	 buffer1, ft_strlen(buffer1));
	return (0);
}*/