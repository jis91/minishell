/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:49:21 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 16:56:20 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real isalpha*/
int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char c;
	char d;
	char e;
	
	c = 'a';
	d = 'F';
	e = '0';
	printf("%d, my ft_isalpha\n", ft_isalpha(c));
	printf("%d, isalpha\n", isalpha(c));
	printf("%d, my ft_isalpha\n", ft_isalpha(d));
	printf("%d, isalpha\n", isalpha(d));
	printf("%d, my ft_isalpha\n", ft_isalpha(e));
	printf("%d, isalpha\n", isalpha(e));
	return (0);
}*/
