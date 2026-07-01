/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:03:00 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 15:10:37 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = lst;
	del(tmp->content);
	free(tmp);
}
/*
static void	delete_node(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*list;
	char	*str;

	str = ft_strdup("Hello World");
	list = ft_lstnew(str);
	if (!list)
	{
		printf("allocation failed\n");
		return (1);
	}
	printf("Node content is : %s\n", (char *)list->content);
	ft_lstdelone(list, delete_node);
	list = NULL;
	if (!list)
	{
		printf("list is empty");
		return (1);
	}
	else
		printf("Node content is : %s\n", (char *)list->content);
	return (0);
}*/
