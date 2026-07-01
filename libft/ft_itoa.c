/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:06:36 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:07:54 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n *= -1;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			len;
	long int	num;

	num = n;
	len = ft_intlen(num);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	result[len--] = 0;
	if (num == 0)
	{
		result[0] = 48;
	}
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		result[len--] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
/*
int	main(void)
{
	int	test;
	char	*result;

	test = -25;
	result = ft_itoa(test);
	printf("%s\n", result);
	return (0);
}*/