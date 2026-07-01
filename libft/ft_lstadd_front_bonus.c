/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:01:21 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 16:09:41 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*node;
	t_list	*node2;
	char	*test;
	char	*test2;

	test = "Hello";
	test2 = "World";
	list = NULL;
	node = ft_lstnew(test);
	node2 = ft_lstnew(test2);

	if (!node || !node2)
	{
		printf("Allocation failed");
		return (1);
	}
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node);
	t_list	*tmp;
	tmp = list;
	while (tmp)
	{
		printf("Node content : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}*/
