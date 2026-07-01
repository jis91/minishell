/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:05:18 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:32:04 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (dsize > 0)
	{
		while (i < dsize - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}
/*
int	main(void)
{
	char	buffer[8];
	char	*msg;
	size_t	len;
	size_t	reallen;

	len = 0;
	reallen = 0;
	msg = "Hello There !";
	len = ft_strlcpy(buffer, msg, sizeof(buffer));
	reallen = strlcpy(buffer, msg, sizeof(buffer));
	printf("FT_STRLCPY; Source length is %zu,\nBuffer : %s\n", len, buffer);
	printf("STRLCPY; Source length is %zu,\nBuffer : %s\n", reallen, buffer);
	return (0);
}*/
