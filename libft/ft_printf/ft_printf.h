/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:06:35 by jeff              #+#    #+#             */
/*   Updated: 2025/10/31 12:58:09 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "../libft.h"

int		ft_printf(const char *format, ...);
int		ft_formats(va_list arguments, const char format);
int		ft_print_char(int c);
void	ft_putstr(char *str);
int		ft_print_str(const char *str);
int		ft_print_pointer(uintptr_t ptr);
int		ft_print_nbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int num, const char format);
int		ft_print_percent(void);

#endif