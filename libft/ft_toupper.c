/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:05:48 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:09:28 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real toupper*/

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/*
int	main(void)
{
	char	c;
	
	c = 'b';
	printf("FT_TOUPPER; %d\n", ft_toupper(c));
	printf("TOUPPER; %d\n", toupper(c));
	return (0);
}*/