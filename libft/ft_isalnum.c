/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:48:25 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 16:44:12 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/ /* Necessary to test the real isalnum*/
int	ft_isalnum(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char	c;
	char	d;
	char	e;
	char	f;

	c = 'a';
	d = 'G';
	e = '8';
	f = '{';
	printf("%d, my ft_isalnum\n",ft_isalnum(c));
	printf("%d, isalnum\n",isalnum(c));
	printf("%d, my ft_isalnum\n",ft_isalnum(d));
	printf("%d, isalnum\n",isalnum(d));
	printf("%d, my ft_isalnum\n",ft_isalnum(e));
	printf("%d, isalnum\n",isalnum(e));
	printf("%d, my ft_isalnum\n",ft_isalnum(f));
	printf("%d, isalnum\n",isalnum(f));
	return (0);
}
*/