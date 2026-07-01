/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:01:10 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:31:51 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while (i + j < len && big[i + j]
			&& little[j] && big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
		j = 0;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*big;
	char	*little;
	char	*result;
	char	*trueresult;

	big = "Hello Grand Master";
	little = "Grand Master";
	result = ft_strnstr(big, little, 18);
	trueresult = strstr(big, little);
	if (result)
		printf("FT_STRNSTR; %s\n", result);
	else
		printf("Not found\n");
	if (trueresult)
		printf("STRNSTR; %s\n", result);
	else
		printf("Not found\n");
	return (0);
}*/
