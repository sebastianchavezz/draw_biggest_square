/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhoppenb <dhoppenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:10:13 by dhoppenb          #+#    #+#             */
/*   Updated: 2023/03/13 22:45:30 by dhoppenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>

void	list_init(t_list *list)
{
	list->buf = NULL;
	list->len = 0;
	list->cap = 0;
}

void	list_free(t_list *list)
{
	free(list->buf);
}

int	list_push(t_list *list, t_coord c)
{
	t_coord	*buf;
	int		i;
	int		cap;

	if (list->len == list->cap)
	{
		cap = (list->cap + 1) * 2;
		buf = malloc(cap * sizeof(*buf));
		if (buf == NULL)
			return (-1);
		i = 0;
		while (i < list->len)
		{
			buf[i] = list->buf[i];
			i++;
		}
		free(list->buf);
		list->buf = buf;
		list->cap = cap;
	}
	list->buf[list->len] = c;
	list->len++;
	return (0);
}
