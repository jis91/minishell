/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:04:13 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/13 19:08:54 by jstrasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>*/ /*Necessary to test the real one*/

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	slen;
	size_t	dlen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dest);
	if (dlen >= dsize)
		dlen = dsize;
	if (dlen == dsize)
		return (dsize + slen);
	if (slen < dsize - dlen)
		ft_memcpy(dest + dlen, src, slen + 1);
	else
	{
		ft_memcpy(dest + dlen, src, dsize - dlen -1);
		dest[dsize - 1] = '\0';
	}
	return (dlen + slen);
}
/*
int	main(void)
{
	char 	*src;
	char	dest[15] = "hello";
	size_t 	tmp;
	size_t	realtmp;

	src = " beautiful creature";
	tmp = ft_strlcat(dest, src, sizeof(dest));
	realtmp = strlcat(dest, src, sizeof(dest));
	printf("FT_STRLCAT; Dest: \"%s\"\n", dest);	//Expected: "hello beautifu"
	
    if (tmp >= sizeof(dest))
	{
		printf("Truncation occurred.\n");
	}
	
	printf("STRLCAT; Dest: \"%s\"\n", dest);	//Expected: "hello beautifu"	
    if (realtmp >= sizeof(dest))
        printf("Truncation occurred.\n");
	
    return (0);
}*/
