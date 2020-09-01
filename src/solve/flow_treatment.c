/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 13:16:30 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:13:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

int		path_lenght(t_room *path)
{
	int i;

	i = 0;
	while (path && path->end != 1)
	{
		i++;
		if (!path->f_to && path->end != 1)
			return (0);
		path = path->f_to;
	}
	return (i);
}

void	print_ant(int ant, char *name)
{
	ft_putstr("L");
	ft_putnbr(ant);
	ft_putstr("-");
	ft_putstr(name);
	ft_putstr(" ");
}

void	path_list(t_bfs **paths, t_list *link)
{
	int		p_size;
	t_room	**actual;

	while (link)
	{
		actual = (t_room**)(link->obj);
		if ((p_size = path_lenght(*actual)))
			insertio(paths, actual, NULL, p_size);
		link = link->next;
	}
}

void	print_path(t_room **path)
{
	t_room	**aux;

	aux = path;
	while ((*aux) && (*aux)->end != 1)
	{
		ft_putstr((*aux)->name);
		ft_putstr(", ");
		aux = &(*aux)->f_to;
	}
	ft_putendl((*aux)->name);
}

void	print_paths(t_bfs **paths)
{
	t_bfs	**aux;

	aux = paths;
	while (*aux)
	{
		ft_putstr("PATH: ");
		print_path((*aux)->room);
		aux = &(*aux)->next;
	}
	ft_putendl("");
}
