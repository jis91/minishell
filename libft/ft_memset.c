/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:03:01 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:08:20 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /* Necessary to test the real one*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *) s;
	while (n > i)
	{
		tmp[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	buffer1[20] = "Love you";
	char	buffer2[20] = "F*ck you";

	printf("before memset: %s\n", buffer1);
	printf("before ft_memset: %s\n", buffer2);
	memset(buffer1, '*', 4);
	ft_memset(buffer2, '*', 4);
	printf("after memset:  %s\n", buffer1);
	printf("after ft_memset: %s\n", buffer2);

    return (0);
}*/
