/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:01:49 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 22:30:10 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;

typedef struct s_square
{
	t_coord	origin;
	int		size;
}			t_square;

typedef struct s_list
{
	int		cap;
	int		len;
	t_coord	*buf;
}			t_list;

void		list_init(t_list *list);
void		list_free(t_list *list);

int			list_push(t_list *list, t_coord crd);

typedef struct s_bsq
{
	t_list	obstacles;
	int		colcount;
	int		rowcount;
	char	chr_empty;
	char	chr_obstacle;
	char	chr_full;
}			t_bsq;

int			read_map(t_bsq *bsq, int fd);

int			solve(t_bsq *bsq, t_square *solution);

void		print_solution(t_bsq *bsq, t_square *solution);

#endif
