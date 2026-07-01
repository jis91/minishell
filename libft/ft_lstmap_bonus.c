/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:16:54 by jstrasse          #+#    #+#             */
/*   Updated: 2025/10/07 16:08:45 by jstrasse         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
static void	delete_node(void *content)
{
	free(content);
}

static void	*node_update(void *content)
{
	char	*str;
	char	*new_str;
	int		i;

	str = (char *)content;
	if (!str)
		return (NULL);
	i = 0;
	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	while (new_str[i])
	{
		new_str[i] = ft_toupper(new_str[i]);
		i++;
	}
	return (new_str);
}

int	main(void)
{
	t_list	*list;
	t_list	*node;
	t_list	*tmp;
	t_list	*new_list;
	char	*str;
	char	*nodestr;

	str = ft_strdup("Hello World !");
	nodestr = ft_strdup("This is Node 1!");

	list = ft_lstnew(str);
	if (!list)
	{
		printf("Allocation failed for list\n");
		return (1);
	}
	node = ft_lstnew(nodestr);
	if (!node)
	{
		printf("Allocation failed for node\n");
		return (1);
	}
	ft_lstadd_back(&list, node);
	tmp = list;

	while (tmp)
	{
		printf("Node content is : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("Mapping through list\n");
	new_list = ft_lstmap(list, node_update, delete_node);
	if (!new_list)
	{
		printf("Mapping failed\n");
		return (1);
	}
	tmp = new_list;
	while (tmp)
	{
		printf("Updated node content is : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&list, delete_node);
	ft_lstclear(&new_list, delete_node);
	return (0);
}*/
