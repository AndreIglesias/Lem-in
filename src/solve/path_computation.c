/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_computation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 12:22:43 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:13:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

int		populate_path(int first, t_bfs **paths, t_bfs **actual)
{
	t_bfs	**aux;
	t_bfs	*nxt;
	int		reach;

	aux = paths;
	reach = 0;
	if (*aux)
		(*aux)->send_ants = first;
	while ((*aux)->next && *aux != *actual)
	{
		reach += (*aux)->send_ants;
		nxt = (*aux)->next;
		nxt->send_ants = (*aux)->send_ants - ft_abs(nxt->path_size -
													(*aux)->path_size);
		aux = &(*aux)->next;
	}
	return (reach + (*aux)->send_ants);
}

int		condemn_path(t_bfs **path, t_bfs **last, int ants)
{
	int	reach;
	int	population;

	reach = 0;
	population = 0;
	while (reach < ants)
	{
		population++;
		reach = populate_path(population, path, last);
	}
	return (population + (*path)->path_size);
}

int		save_min(t_bfs **paths, int turn)
{
	t_bfs	**aux;

	turn = (turn) ? turn : 0;
	aux = paths;
	while (*aux && (*aux)->send_ants != 0)
	{
		(*aux)->min_ants = (*aux)->send_ants;
		aux = &(*aux)->next;
	}
	return (turn);
}

void	path_config(t_bfs **path, int ants)
{
	t_bfs	**aux;
	int		turn;
	int		min;

	aux = path;
	min = -1;
	while (*aux)
	{
		turn = condemn_path(path, aux, ants);
		if (turn < min || min < 0)
			min = save_min(path, turn);
		if ((*aux)->send_ants == 0)
			break ;
		aux = &(*aux)->next;
	}
}
