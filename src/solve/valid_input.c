/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 16:56:41 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/19 00:23:28 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

int		endpoints(t_room *room1)
{
	int	start;
	int	end;

	if (!room1)
		return (0);
	start = 0;
	end = 0;
	while (room1)
	{
		if (room1->start)
			start++;
		if (room1->end)
			end++;
		room1 = room1->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (ft_puterr("ERROR:Improper number of endpoints", 0));
}
