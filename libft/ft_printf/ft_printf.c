/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:34:07 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/31 13:02:02 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list arguments, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_print_char(va_arg(arguments, int));
	else if (format == 's')
		print_length += ft_print_str(va_arg(arguments, char *));
	else if (format == 'p')
		print_length += ft_print_pointer(va_arg(arguments, uintptr_t));
	else if (format == 'd' || format == 'i')
		print_length += ft_print_nbr(va_arg(arguments, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(arguments, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(arguments, unsigned int), format);
	else if (format == '%')
		print_length += ft_print_percent();
	return (print_length);
}

int	ft_printf(const char *format, ...)
{
	int			i;
	va_list		arguments;
	int			print_length;

	i = 0;
	print_length = 0;
	va_start(arguments, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			print_length += ft_formats(arguments, format[i +1]);
			i++;
		}
		else
			print_length += ft_print_char(format[i]);
		i++;
	}
	va_end(arguments);
	return (print_length);
}
