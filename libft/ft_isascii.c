/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:49:43 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 16:56:15 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real isascii*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char	c;
	char	a;

	c ='@';
	a = 128;
	printf("%d, my ft_isascii\n",ft_isascii(c));
	printf("%d, isascii\n",isascii(c));
	printf("%d, my ft_isascii\n",ft_isascii(a));
	printf("%d, isascii\n",isascii(a));
	return (0);
}*/
