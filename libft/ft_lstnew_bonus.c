/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:59:15 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 11:59:20 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
int main(void)
{
	t_list	*node;
	char	*str;
	
	str = "Hello, linked list!";
	node = ft_lstnew(str);
	if (!node)
	{
		printf("Failed to allocate memory for new node.\n");
		return (1);
	}
	printf("Node content: %s\n", (char *)node->content);
	printf("Node next: %p\n", (void *)node->next);
	free(node);
	return (0);
}*/
