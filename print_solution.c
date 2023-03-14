/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:32 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 22:52:07 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>

static void	print_cell(t_bsq *bsq, t_square *solution, int col, int row)
{
	int		i;
	t_coord	c;
	int		s;

	c = solution->origin;
	s = solution->size;
	if (c.x <= col && col < c.x + s && c.y <= row && row < c.y + s)
	{
		write(1, &bsq->chr_full, 1);
		return ;
	}
	i = 0;
	while (i < bsq->obstacles.len)
	{
		c = bsq->obstacles.buf[i];
		if (c.x == col && c.y == row)
		{
			write(1, &bsq->chr_obstacle, 1);
			return ;
		}
		i++;
	}
	write(1, &bsq->chr_empty, 1);
}

static void	print_line(t_bsq *bsq, t_square *solution, int row)
{
	int	col;

	col = 0;
	while (col < bsq->colcount)
	{
		print_cell(bsq, solution, col, row);
		col++;
	}
	write(1, "\n", 1);
}

void	print_solution(t_bsq *bsq, t_square *solution)
{
	int	row;

	row = 0;
	while (row < bsq->rowcount)
	{
		print_line(bsq, solution, row);
		row++;
	}
}
