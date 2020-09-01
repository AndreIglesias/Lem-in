/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:04:29 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 12:56:53 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include "libft.h"

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_room
{
	char			*name;
	t_coord			c;
	int				ant;
	int				start;
	int				end;
	t_list			*lnks;
	struct s_room	*f_to;
	struct s_room	*f_fm;
	struct s_room	*next;
}					t_room;

/*
** /list/
*/
void				add_link(t_room **room1, char *name1, char *name2);
void				pop_link(t_list **link);
void				destruct_link(t_list **link);
void				print_link(t_list *link);

/*
** /room/
*/
void				init_room(t_room **room, char *name, t_coord c, int io);
void				pop_room(t_room **room1);
void				destruct_room(t_room **room);
void				push_room(t_room **room1, char *name, t_coord c, int io);
void				print_room(t_room *room);

int					is_name(t_room *room1, char *name);
t_room				**find_name(t_room **room1, char *name);
int					is_coords(t_room *room1, char *x, char *y);
t_room				**find_start(t_room **room1);
t_room				**find_end(t_room **room1);

#endif
