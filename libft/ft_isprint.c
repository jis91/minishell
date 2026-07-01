/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:50:21 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:07:42 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real isprint*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char	c;
	char	d;

	c = 32;
	d = 30;

	printf("%d, my ft_isprint\n", ft_isprint(c));
	printf("%d, isprint\n", isprint(c));
	printf("%d, my ft_isprint\n", ft_isprint(d));
	printf("%d, isprint\n", isprint(d));
	return (0);
}*/