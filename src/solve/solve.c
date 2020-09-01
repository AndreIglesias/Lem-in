/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 16:46:47 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 13:13:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

int		solve(t_farm **farm, int debug)
{
	t_bfs	*p;
	t_room	**start;
	int		apath;

	if (!endpoints((*farm)->rms))
		return (0);
	apath = 2;
	while (apath)
	{
		if (!(start = find_start(&(*farm)->rms)))
			return (0);
		p = NULL;
		insert_bfs(&p, start, NULL);
		if (apath == 2 && !(apath = bfs(&p, &p)))
			return (free_pile(&p) + ft_puterr("ERROR:Unreachable endpoint", 0));
		else
			apath = bfs(&p, &p);
		update_flow(&p);
		(debug) ? print_bfs(p) : 0;
		free_pile(&p);
		if ((*farm)->ants <= 1)
			break ;
	}
	send_ants(farm, find_start(&(*farm)->rms), debug, 0);
	return (1);
}
