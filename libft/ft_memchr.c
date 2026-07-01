/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:18:10 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:31:21 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /* Necessary to test the real one*/
void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*srctmp;
	unsigned char	ctmp;

	i = 0;
	srctmp = (unsigned char *)src;
	ctmp = (unsigned char) c;
	while (i < n)
	{
		if (srctmp[i] == ctmp)
			return ((void *)&srctmp[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*src;
	char	*result;
	char	*trueresult;
	
	src = "Hello Gangsta";
	result = ft_memchr(src, 'g', 12);
	trueresult = memchr(src, 'g', 12);
	if (result)
		printf("FT_MEMCHR; Found: '%c' at position %ld\n",
		 *result, result - src);
	else
		printf("Character not found in source\n");
	if (trueresult)
		printf("MEMCHR; Found: '%c' at position %ld\n",
		 *trueresult, trueresult - src);
	else
		printf("Character not found in source\n");
	return (0);
}*/