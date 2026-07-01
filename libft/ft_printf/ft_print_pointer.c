/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:00:12 by jeff              #+#    #+#             */
/*   Updated: 2025/10/21 10:23:32 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/* These functions are helpers for print_pointer*/
static void	ft_put_pointer(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_put_pointer(ptr / 16);
		ft_put_pointer(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
		{
			ft_print_char((ptr + '0'));
		}
		else
		{
			ft_print_char((ptr - 10 + 'a'));
		}
	}
}

static int	ft_pointer_length(uintptr_t ptr)
{
	int	length;

	length = 0;
	while (ptr != 0)
	{
		length++;
		ptr /= 16;
	}
	return (length);
}

/* End of helpers for print_pointer*/
int	ft_print_pointer(uintptr_t ptr)
{
	int	print_length;

	print_length = 0;
	if (ptr == 0)
	{
		print_length += write(1, "(nil)", 5);
	}
	else
	{
		print_length += write(1, "0x", 2);
		ft_put_pointer(ptr);
		print_length += ft_pointer_length(ptr);
	}
	return (print_length);
}
