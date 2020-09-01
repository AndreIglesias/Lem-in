/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:47:42 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/19 00:21:51 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

int		is_linked(t_list *link, t_room *room)
{
	while (link)
	{
		if (*((t_room**)(link->obj)) == room)
			return (1);
		link = link->next;
	}
	return (0);
}

void	add_link(t_room **room1, char *name1, char *name2)
{
	t_room	**r1;
	t_room	**r2;
	t_list	*new1;
	t_list	*new2;

	r1 = find_name(room1, name1);
	r2 = find_name(room1, name2);
	if (!is_linked((*r1)->lnks, *r2))
	{
		new1 = ft_lstnew2((void*)r2, sizeof(t_room**));
		ft_lstadd(&((*r1)->lnks), new1);
	}
	if (!is_linked((*r2)->lnks, *r1))
	{
		new2 = ft_lstnew2((void*)r1, sizeof(t_room**));
		ft_lstadd(&((*r2)->lnks), new2);
	}
}

void	pop_link(t_list **link)
{
	t_list	*next_node;

	if (*link == NULL)
		return ;
	next_node = (*link)->next;
	free(*link);
	*link = next_node;
}

void	destruct_link(t_list **link)
{
	while (*link)
		pop_link(link);
}

int		size_link(t_list *link)
{
	int	i;

	i = 0;
	while (link)
	{
		i++;
		link = link->next;
	}
	return (i);
}
