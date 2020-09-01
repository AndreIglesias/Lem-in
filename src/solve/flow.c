/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 13:07:03 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:13:23 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

void	update_flow(t_bfs **p)
{
	t_bfs	**aux;
	t_room	**r;
	t_room	**prv;

	aux = p;
	while (*aux && (*((*aux)->room))->end != 1)
		aux = &(*aux)->next;
	while (*aux)
	{
		r = ((*aux)->room);
		prv = ((*aux)->prev) ? ((*aux)->prev)->room : NULL;
		if ((*aux)->prev && !((*r)->f_to == *prv || (*prv)->f_fm == *r))
		{
			if (((*r)->end != 1 && (*r)->start != 1) ||
				((*r)->end == 1 && (*prv)->start == 1))
				(*r)->f_fm = *prv;
			if ((*prv)->start != 1)
				(*prv)->f_to = *r;
		}
		if ((*aux)->prev && (*r)->f_to == *prv)
			(*r)->f_to = NULL;
		if ((*aux)->prev && (*prv)->f_fm == *r)
			(*prv)->f_fm = NULL;
		aux = &(*aux)->prev;
	}
}

int		push_ants(t_room **path, int entro)
{
	t_room	**aux;
	int		prev_ant;
	int		aux_ant;

	aux = path;
	prev_ant = 0;
	while ((*aux) && (*aux)->end != 1)
	{
		aux_ant = (*aux)->ant;
		(*aux)->ant = prev_ant;
		prev_ant = aux_ant;
		if ((*aux)->ant)
		{
			entro = 1;
			print_ant((*aux)->ant, (*aux)->name);
		}
		aux = &(*aux)->f_to;
	}
	if (prev_ant && (*aux) && (*aux)->end == 1)
	{
		(*aux)->ant++;
		print_ant(prev_ant, (*aux)->name);
	}
	return (entro);
}

int		move_ants(t_bfs **paths)
{
	t_bfs	**aux;
	int		entro;

	entro = 0;
	aux = paths;
	while (*aux)
	{
		entro += push_ants((*aux)->room, 0);
		aux = &(*aux)->next;
	}
	return (entro);
}

int		select_paths(t_bfs **paths, t_farm **farm, int ants)
{
	t_bfs	**aux;
	int		entro;

	entro = 0;
	aux = paths;
	while (*aux && (*farm)->ants && (*aux)->min_ants)
	{
		entro = 1;
		(*aux)->min_ants--;
		(*(*aux)->room)->ant = ants - (*farm)->ants + 1;
		print_ant((*(*aux)->room)->ant, (*(*aux)->room)->name);
		(*farm)->ants--;
		aux = &(*aux)->next;
	}
	return (entro);
}

void	send_ants(t_farm **farm, t_room **start, int debug, int turns)
{
	t_bfs	*paths;
	int		ants;
	t_room	**end;
	int		entro;

	paths = NULL;
	ants = (*farm)->ants;
	end = find_end(&(*farm)->rms);
	path_list(&paths, (*start)->lnks);
	path_config(&paths, ants);
	(debug) ? print_paths(&paths) : 0;
	while ((*end)->ant < ants)
	{
		turns++;
		entro = move_ants(&paths);
		entro += select_paths(&paths, farm, ants);
		ft_putendl("");
		if (!entro)
			break ;
	}
	(debug) ? ft_putstr("\nTurns: ") : 0;
	(debug) ? ft_putnbr(turns) : 0;
	(debug) ? ft_putendl("") : 0;
	free_pile(&paths);
}
