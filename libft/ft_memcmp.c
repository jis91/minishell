/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:46:55 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 17:03:28 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /* Necessary to test the real one*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1tmp;
	unsigned char	*s2tmp;
	size_t			i;

	i = 0;
	s1tmp = (unsigned char *)s1;
	s2tmp = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1tmp[i] != s2tmp[i])
			return (s1tmp[i] - s2tmp[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*msg;
	char	*test;

	msg = "Hello";
	test = "Hfllo";
	printf("%d, FT_MEMCMP\n", ft_memcmp(msg, test, 5));
	printf("%d, MEMCMP\n", memcmp(msg, test, 5));
	return (0);
}*/
