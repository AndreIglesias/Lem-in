/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:47:43 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/19 00:22:53 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "farm.h"

int		add_ants(t_farm **farm, int ants)
{
	(*farm)->ants = ants;
	return (1);
}

void	init_farm(t_farm **farm)
{
	*farm = NULL;
	if (!(*farm = (t_farm*)malloc(sizeof(t_farm))))
		return ;
	add_ants(farm, 0);
	(*farm)->rms = NULL;
}

void	destruct_farm(t_farm **farm)
{
	destruct_room(&((*farm)->rms));
	if (*farm)
		free(*farm);
}

void	print_farm(t_farm *farm)
{
	ft_putendl("\n_________________");
	ft_putstr("Ants: ");
	ft_putnbr(farm->ants);
	ft_putendl("\n_________________");
	print_room(farm->rms);
}

t_coord	coord(char *x, char *y)
{
	t_coord c;

	c.x = ft_atoi(x);
	c.y = ft_atoi(y);
	return (c);
}
