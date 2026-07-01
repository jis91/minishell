/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:02:33 by jeff              #+#    #+#             */
/*   Updated: 2025/10/20 16:05:53 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* These functions are helpers for print_hex*/
static int	ft_hex_length(unsigned int n)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		length++;
		n /= 16;
	}
	return (length);
}

static void	ft_put_hex(unsigned int n, const char format)
{
	if (n >= 16)
	{
		ft_put_hex(n / 16, format);
		ft_put_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				ft_print_char(n - 10 + 'a');
			if (format == 'X')
				ft_print_char(n - 10 + 'A');
		}
	}
}

/* End of helpers for print_hex*/
int	ft_print_hex(unsigned int n, const char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(n, format);
	return (ft_hex_length(n));
}
