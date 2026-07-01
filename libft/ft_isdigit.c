/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:50:06 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 16:56:09 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real isdigit*/
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char c;
	char d;

	c = 'a';
	d = '7';

	printf("%d, my ft_isdigit\n", ft_isdigit(c));
	printf("%d, isdigit\n", isdigit(c));
	printf("%d, my ft_isdigit\n", ft_isdigit(d));
	printf("%d, isdigit\n", isdigit(d));
	return (0);
}*/
