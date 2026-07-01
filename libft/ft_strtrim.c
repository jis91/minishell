/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:33:56 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:01:17 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strrchr(set, s1[end]))
		end--;
	result = ft_substr(s1, start, (end - start) + 1);
	return (result);
}
/*
int	main(void)
{
	char *test;
	char *result;
	
	test = "ABABHelloBABA";
	result = ft_strtrim(test, "AB");
	printf("%s\n", result);
	return (0);
}*/
