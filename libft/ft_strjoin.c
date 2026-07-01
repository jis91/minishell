/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:06:35 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/01 16:36:29 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	total;

	i = 0;
	j = 0;
	total = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	total = j + i;
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (total + 1));
	if (!result)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*test;
	char	*essai;
	char	*result;

	test = "Hello";
	essai = " there !";
	result = ft_strjoin(test, essai);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
