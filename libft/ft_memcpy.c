/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:51:16 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:08:09 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /* Necessary to test the real one*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srctmp;
	unsigned char	*desttmp;

	srctmp = (unsigned char *) src;
	desttmp = (unsigned char *) dest;
	i = 0;
	if (!(dest || src))
		return (NULL);
	while (i < n)
	{
		desttmp[i] = srctmp[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	*src;
	char	dest[20];
	char	truedest[20];

	src = "Hello there !";
	ft_memcpy(dest, src, (ft_strlen(src) + 1));
	memcpy(truedest, src, (ft_strlen(src) + 1));
	printf("%s, FT_MEMCPY\n", dest);
	printf("%s, MEMCPY\n", truedest);
	return (0);
}*/
