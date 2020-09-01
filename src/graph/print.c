/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 00:15:49 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:12:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_link(t_list *link)
{
	while (link)
	{
		ft_putstr((*((t_room**)(link->obj)))->name);
		if (link->next)
			ft_putstr(", ");
		link = link->next;
	}
	ft_putendl("");
}

void	print_room(t_room *room)
{
	while (room)
	{
		ft_putstr("Name: ");
		ft_putendl(room->name);
		ft_putstr("(start/end): (");
		ft_putnbr(room->start);
		ft_putstr("/");
		ft_putnbr(room->end);
		ft_putendl(")");
		ft_putstr("Coords: (");
		ft_putnbr(room->c.x);
		ft_putstr(", ");
		ft_putnbr(room->c.y);
		ft_putendl(")");
		ft_putstr("Links: ");
		print_link(room->lnks);
		ft_putstr("Flow to: ");
		ft_putstr((room->f_to) ? room->f_to->name : "*");
		ft_putstr("\nFlow from: ");
		ft_putstr((room->f_fm) ? room->f_fm->name : "*");
		ft_putendl("\n");
		room = room->next;
	}
}
