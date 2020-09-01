/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:59:08 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:13:19 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

void	init_bfs(t_bfs **p, t_room **room, t_bfs *prev, int p_size)
{
	*p = NULL;
	if (!(*p = (t_bfs*)malloc(sizeof(t_bfs))))
		return ;
	(*p)->path_size = p_size;
	(*p)->send_ants = 0;
	(*p)->min_ants = 0;
	(*p)->room = room;
	(*p)->prev = prev;
	(*p)->next = NULL;
}

void	insertio(t_bfs **p, t_room **room, t_bfs *prev, int p_size)
{
	t_bfs *new;
	t_bfs **aux;

	init_bfs(&new, room, prev, p_size);
	if (!*p)
	{
		*p = new;
	}
	else
	{
		aux = p;
		while ((*aux)->next && (*aux)->next->path_size < p_size)
			aux = &(*aux)->next;
		if (aux == p && (*p)->path_size > p_size)
		{
			new->next = *p;
			*p = new;
		}
		else
		{
			new->next = (*aux)->next;
			(*aux)->next = new;
		}
	}
}

void	insert_bfs(t_bfs **p, t_room **room, t_bfs *prev)
{
	t_bfs *new;
	t_bfs **aux;

	init_bfs(&new, room, prev, 0);
	if (!*p)
	{
		*p = new;
	}
	else
	{
		aux = p;
		while ((*aux)->next)
			aux = &(*aux)->next;
		(*aux)->next = new;
	}
}

void	pop_pile(t_bfs **p)
{
	t_bfs	*next_node;

	if (*p == NULL)
		return ;
	next_node = (*p)->next;
	free(*p);
	*p = next_node;
}

int		free_pile(t_bfs **p)
{
	while (*p)
		pop_pile(p);
	return (0);
}
