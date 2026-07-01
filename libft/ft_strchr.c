/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:03:51 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:32:54 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/
char	*ft_strchr(const char *src, int c)
{
	size_t	i;
	char	a;

	a = (char) c;
	i = 0;
	while (src[i])
	{
		if (src[i] == a)
			return ((char *)&src[i]);
		i++;
	}
	if (src[i] == a)
		return ((char *) &src[i]);
	return (NULL);
}
/*
int	main(void)
{
	char	*src;
	char	*result;
	char	*trueresult;

	src = NULL;
	result = ft_strchr(src, 'g');	
	trueresult = strchr(src, 'g');
	if (result)
		printf("FT_STRCHR; Found: '%c' at position %ld\n",
		 *result, result - src);
	else 
		printf("Character not found in source\n");
	if (trueresult)
		printf("STRCHR; Found: '%c' at position %ld\n",
		 *trueresult, trueresult - src);
	else 
		printf("Character not found in source\n");
	return (0);
}*/