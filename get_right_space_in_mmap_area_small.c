/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_space_in_mmap_area_small.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:58:43 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/14 18:09:21 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*set_right_space_as_allocated_small(t_sarea *area, int nb, int i)
{
	int j;

	j = 0;
	while (j < nb)
	{
		((area->bstatus)[i + j]).free = 0;
		if (j == 0)
			((area->bstatus)[i + j]).nbblocks = nb;
		else
			((area->bstatus)[i + j]).nbblocks = 0;
		j++;
	}
	return ((char*)(&((area->blocks)[i])));
}

void	*get_right_space_in_mmap_area_small(t_sarea *area, size_t size)
{
	int i;
	int j;
	int nb;

	i = 0;
	nb = (1 + (size - 1) / SMALL);
	while (i < SBLOCKS)
	{
		j = 0;
		while (i + j < SBLOCKS && j < 5 && j < nb)
		{
			if (((area->bstatus)[i + j]).free == 1)
				j++;
			else
				break ;
		}
		if (j == nb)
			return ((void*)set_right_space_as_allocated_small(area, nb, i));
		i++;
	}
	return (NULL);
}
