/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:13:39 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 14:18:33 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}
/*
static void	content_update(void *content)
{
	char	*str = (char *)content;
	int	i;
	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

int	main(void)
{
	t_list	*list;
	t_list	*node;
	t_list	*tmp;
	char	*str;
	char	*nodestr;
	
	str = ft_strdup("Hello World!");
	nodestr = ft_strdup("This is node 1");
	list = ft_lstnew(str);
	if (!list)
	{
		printf("Allocation failed for list");
		return (1);
	}
	node = ft_lstnew(nodestr);
	if (!node)
	{
		printf("Allocation failed for node");
		return (1);
	}
	ft_lstadd_back(&list, node);
	tmp = list;
	while (tmp)
	{
		printf("Node content is : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("Iterating and uppercasing nodes\n");
	ft_lstiter(list, content_update);
	tmp = list;
	while (tmp)
	{
		printf("Updated node content is : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}*/
