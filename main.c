/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:40:41 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 22:49:55 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <fcntl.h>
#include <unistd.h>

static int	map_error(void)
{
	write(2, "map error\n", 10);
	return (0);
}

static int	bsq(int fd)
{
	t_bsq		b;
	t_square	sln;

	if (read_map(&b, fd) < 0)
		return (-1);
	if (solve(&b, &sln) < 0)
	{
		list_free(&b.obstacles);
		return (-1);
	}
	print_solution(&b, &sln);
	list_free(&b.obstacles);
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	ret;

	ret = 0;
	if (argc <= 1)
	{
		if (bsq(0) < 0)
			ret = map_error();
	}
	else
	{
		while (*++argv)
		{
			fd = open(*argv, O_RDONLY);
			if (fd < 0)
			{
				ret = map_error();
				continue ;
			}
			if (bsq(fd) < 0)
				ret = map_error();
			close(fd);
		}
	}
	return (ret);
}
