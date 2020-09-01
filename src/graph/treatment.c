/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:58:34 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/19 00:21:21 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	init_room(t_room **room, char *name, t_coord c, int io)
{
	*room = NULL;
	if (!(*room = (t_room*)malloc(sizeof(t_room))))
		return ;
	(*room)->name = ft_strdup(name);
	(*room)->c = c;
	(*room)->start = 0;
	(*room)->ant = 0;
	(*room)->end = 0;
	if (io >= 0)
	{
		if (io == 0)
			(*room)->start = 1;
		else if (io == 1)
			(*room)->end = 1;
	}
	(*room)->lnks = NULL;
	(*room)->f_to = NULL;
	(*room)->f_fm = NULL;
	(*room)->next = NULL;
}

void	pop_room(t_room **room)
{
	t_room	*next_node;

	if (*room == NULL)
		return ;
	next_node = (*room)->next;
	destruct_link(&(*room)->lnks);
	free((*room)->name);
	free(*room);
	*room = next_node;
}

void	destruct_room(t_room **room)
{
	while (*room)
		pop_room(room);
}

void	push_room(t_room **room1, char *name, t_coord c, int io)
{
	t_room *new;

	init_room(&new, name, c, io);
	new->next = *room1;
	*room1 = new;
}
