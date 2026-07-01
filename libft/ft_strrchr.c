/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:12:22 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:34:25 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/

char	*ft_strrchr(const char *src, int c)
{
	size_t	i;
	char	*result;
	char	a;

	a = (char) c;
	result = NULL;
	i = 0;
	while (src[i])
	{
		if (src[i] == a)
			result = (char *) &src[i];
		i++;
	}
	if (src[i] == a)
		result = (char *) &src[i];
	return (result);
}
/*
int     main(void)
{
        char    *src;
        char    *result;
		char	*trueresult;

        src = "Hello Ggangsta";
        result = ft_strrchr(src, 'g');   
		trueresult = strrchr(src, 'g');
        if (result)
                printf("FT_STRRCHR; Found: '%c' at position %ld\n",
				 *result, result - src);
        else 
		{
                printf("Character not found in source\n");
		}
		if (trueresult)
                printf("STRRCHR; Found: '%c' at position %ld\n",
				 *trueresult, trueresult - src);
        else 
                printf("Character not found in source\n");
        return (0);
}*/
