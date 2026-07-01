/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:08:11 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:31:57 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/
char	*ft_strdup(const char *src)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (src == 0)
		return (NULL);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
int	main(void)
{
	char	*src;
	char	*result;
	char	*trueresult;

	src = NULL;
	result = ft_strdup(src);
	trueresult = strdup(src);
	printf("FT_STRDUP : %s\n", result);
	printf("STRDUP : %s\n", trueresult);
	return (0);
}*/
