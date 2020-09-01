/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 00:32:18 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 02:29:25 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "farm.h"

int		is_num(char *str)
{
	int i;

	i = 0;
	if (str[i])
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i++]))
				return (0);
		}
		if (exceeds_int(str))
			return (0);
		return (1);
	}
	return (0);
}

int		is_room(t_room **rms, char **rooms, int *io)
{
	int i;

	if (!rooms || !(rooms[0]))
		return (0);
	if (rooms[0] && (rooms[0][0] == 'L' || rooms[0][0] == '#'))
		return (0);
	i = 1;
	while (rooms[i])
	{
		if (!is_num(rooms[i]))
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	if (is_name(*rms, rooms[0]))
		return (-1 + ft_puterr("ERROR:Room already exists", 0));
	if (is_coords(*rms, rooms[1], rooms[2]))
		return (-1 + ft_puterr("ERROR:Coordinates not available", 0));
	push_room(rms, rooms[0], coord(rooms[1], rooms[2]), *io);
	return (1);
}

int		is_link(t_farm **farm, char *str, int io)
{
	char	**links;
	int		i;

	if (io != -1)
		return (ft_puterr("ERROR:Improper data type", 0));
	if (!(links = ft_strsplit(str, '-')) || ft_countchr(str, '-') > 1)
		return (free_split(links) + ft_puterr("ERROR:Improper format", 0));
	i = 0;
	while (links[i])
		i++;
	if (i == 0)
		return (free_split(links));
	if (i != 2)
		return (free_split(links) + ft_puterr("ERROR:Improper format", 0));
	if (ft_strcmp(links[0], links[1]) == 0 ||
		(!is_name((*farm)->rms, links[0]) || !is_name((*farm)->rms, links[1])))
		return (free_split(links) + ft_puterr("ERROR:Improper linked room", 0));
	add_link(&((*farm)->rms), links[0], links[1]);
	return (free_split(links) + 1);
}

int		repeated_endpoints(int *start, int *end, int io, int section)
{
	if ((*start) && io == 0)
		return (-1 + ft_puterr("ERROR:Improper or repeated start", 0));
	if ((*end) && io == 1)
		return (-1 + ft_puterr("ERROR:Improper or repeated end", 0));
	if (!(*start) && io == 0)
		*start = 1;
	if (!(*end) && io == 1)
		*end = 1;
	return (section);
}
