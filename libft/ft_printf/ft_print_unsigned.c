/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:01:44 by jeff              #+#    #+#             */
/*   Updated: 2025/10/20 16:02:15 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* These functions are helpers for print_unsigned*/
static int	ft_num_length(unsigned int n)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*num;
	size_t	length;

	length = ft_num_length(n);
	num = (char *)malloc(sizeof(char) * (length +1));
	if (!num)
	{
		return (NULL);
	}
	num[length] = 0;
	while (n != 0)
	{
		num[length - 1] = n % 10 + '0';
		n /= 10;
		length--;
	}
	return (num);
}

/* End of helpers for print_unsigned*/
int	ft_print_unsigned(unsigned int n)
{
	int		print_length;
	char	*num;

	print_length = 0;
	if (n == 0)
		print_length += write(1, "0", 1);
	else
	{
		num = ft_uitoa(n);
		print_length += ft_print_str(num);
		free(num);
	}
	return (print_length);
}
