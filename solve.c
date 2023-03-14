/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:33 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 23:20:40 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

static int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

static void	try_cell(t_bsq *bsq, t_square *sln, int col, int row)
{
	int		i;
	int		largest;
	int		dist;
	t_coord	c;

	i = 0;
	largest = ft_min(bsq->rowcount - row, bsq->colcount - col);
	while (i < bsq->obstacles.len)
	{
		c = bsq->obstacles.buf[i];
		if (c.x >= col && c.y >= row)
		{
			dist = ft_max(c.x - col, c.y - row);
			largest = ft_min(largest, dist);
		}
		i++;
	}
	if (sln->size < largest)
	{
		sln->origin.x = col;
		sln->origin.y = row;
		sln->size = largest;
	}
}

static void	try_row(t_bsq *bsq, t_square *sln, int row)
{
	int	col;

	col = 0;
	while (col < bsq->colcount)
	{
		try_cell(bsq, sln, col, row);
		col++;
	}
}

int	solve(t_bsq *bsq, t_square *solution)
{
	int	row;

	row = 0;
	solution->size = 0;
	while (row < bsq->rowcount)
	{
		try_row(bsq, solution, row);
		row++;
	}
	return (-(solution->size == 0));
}
