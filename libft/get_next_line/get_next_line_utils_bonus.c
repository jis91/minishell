/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:09:12 by jeff              #+#    #+#             */
/*   Updated: 2025/10/29 18:09:16 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		printf("src is NULL");
		return (-1);
	}
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *src, int c)
{
	size_t	i;
	char	a;

	a = (char) c;
	i = 0;
	if (src == NULL)
	{
		printf("src is NULL");
		return (NULL);
	}
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

void	ft_check_src(char *s1)
{
	s1 = malloc(sizeof(char) * 1);
	if (!s1)
		return ;
	s1[0] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
		ft_check_src(s1);
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	free(s1);
	return (result);
}
