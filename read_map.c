/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:32 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 22:49:32 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>

static int	read_init_valid(t_bsq *bsq)
{
	int	valid;

	valid = bsq->rowcount != 0;
	valid &= bsq->chr_empty != bsq->chr_obstacle;
	valid &= bsq->chr_empty != bsq->chr_full;
	valid &= bsq->chr_obstacle != bsq->chr_full;
	return (-(!valid));
}

static int	read_init(t_bsq *bsq, int fd)
{
	char	c;
	int		valid;
	int		len;

	bsq->rowcount = 0;
	valid = 0;
	while (1)
	{
		len = read(fd, &c, 1);
		if (len <= 0)
			return (-1);
		if (c == '\n')
			return (read_init_valid(bsq));
		valid++;
		if (valid >= 4)
		{
			bsq->rowcount *= 10;
			bsq->rowcount += bsq->chr_empty - '0';
		}
		bsq->chr_empty = bsq->chr_obstacle;
		bsq->chr_obstacle = bsq->chr_full;
		bsq->chr_full = c;
	}
}

static int	read_map_line(t_bsq *bsq, int row, int fd)
{
	char	c;
	int		len;
	t_coord	crd;

	crd.x = 0;
	crd.y = row;
	while (1)
	{
		len = read(fd, &c, 1);
		if (len <= 0)
			return (-1);
		if (c == '\n')
			break ;
		if (c == bsq->chr_obstacle)
		{
			if (list_push(&bsq->obstacles, crd) < 0)
				return (-1);
		}
		else if (c != bsq->chr_empty)
			return (-1);
		crd.x++;
	}
	if (bsq->colcount == 0)
		bsq->colcount = crd.x;
	return (-(bsq->colcount != crd.x));
}

int	read_map(t_bsq *bsq, int fd)
{
	int	i;

	if (read_init(bsq, fd) < 0)
		return (-1);
	i = 0;
	bsq->colcount = 0;
	list_init(&bsq->obstacles);
	while (i < bsq->rowcount)
	{
		if (read_map_line(bsq, i, fd) < 0)
		{
			list_free(&bsq->obstacles);
			return (-1);
		}
		i++;
	}
	return (0);
}
