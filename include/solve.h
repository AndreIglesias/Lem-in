/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 22:38:16 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 02:41:19 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "lem_in.h"

typedef struct		s_bfs
{
	int				path_size;
	int				send_ants;
	int				min_ants;
	t_room			**room;
	struct s_bfs	*prev;
	struct s_bfs	*next;
}					t_bfs;

void				insertio(t_bfs **p, t_room **room, t_bfs *prev, int p_size);
void				insert_bfs(t_bfs **p, t_room **room, t_bfs *prev);
int					free_pile(t_bfs **p);

int					bfs(t_bfs **p, t_bfs **current);
int					endpoints(t_room *room1);

int					solve(t_farm **farm, int debug);
void				path_config(t_bfs **path, int ants);

void				print_bfs(t_bfs *p);
void				print_paths(t_bfs **paths);
void				print_ant(int ant, char *name);
void				path_list(t_bfs **paths, t_list *link);

void				update_flow(t_bfs **p);
int					push_ants(t_room **path, int entro);
int					move_ants(t_bfs **paths);
int					select_paths(t_bfs **paths, t_farm **farm, int ants);
void				send_ants(t_farm **farm, t_room **start, int debug, int t);

#endif
