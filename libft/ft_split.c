/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:06:07 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/02 17:03:10 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	trigger;

	i = 0;
	j = 0;
	trigger = 0;
	while (s[i])
	{
		if (s[i] != c && trigger == 0)
		{
			trigger = 1;
			j++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (j);
}

static void	*free_split(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*fill_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static int	split_loop(const char *s, char c, char **result, size_t len)
{
	size_t	i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = -1;
	while (i <= len)
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			result[j] = fill_word(s, start, i);
			if (!result[j])
			{
				free_split(result, j);
				return (0);
			}
			j++;
			start = -1;
		}
		i++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char		**result;

	result = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	if (!split_loop(s, c, result, ft_strlen(s)))
		return (NULL);
	return (result);
}
/*
int	main(void)
{
	char	*test;
	char	c;
	char	**result;
	int		i;

	i = 0;
	test = "Hello World This Is Split";
	c = 32;
	result = ft_split(test, c);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}*/
