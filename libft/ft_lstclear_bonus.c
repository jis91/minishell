/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:07:29 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 14:04:09 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}
/*
static void	delete_node(void *content)
{
	free(content);
}
int	main(void)
{
	t_list	*list;
	t_list	*node;
	char	*str;
	char	*nodestr;

	str = ft_strdup("Hello World!");
	nodestr = ft_strdup("Node 1");

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
	while (list)
	{
		printf("Node content is : %s\n", (char *)list->content);
		list = list->next;
	}
	ft_lstclear(&list, delete_node);
	printf("List has been cleared\n");
	if (!list)
	{
		printf("List is empty");
		return (1);
	}
	else 
	{
		printf("Node content is : %s\n", (char *)list->content);
		return (0);
	}
	return (0);
}*/
