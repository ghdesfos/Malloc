/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_space_in_mmap_area_medium.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:22:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/14 18:09:09 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*set_right_space_as_allocated_medium(t_marea *area, int nb, int i)
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

void	*get_right_space_in_mmap_area_medium(t_marea *area, size_t size)
{
	int i;
	int j;
	int nb;

	i = 0;
	nb = (1 + (size - 1) / MEDIUM);
	while (i < MBLOCKS)
	{
		j = 0;
		while (i + j < MBLOCKS && j < 5 && j < nb)
		{
			if (((area->bstatus)[i + j]).free == 1)
				j++;
			else
				break ;
		}
		if (j == nb)
			return ((void*)set_right_space_as_allocated_medium(area, nb, i));
		i++;
	}
	return (NULL);
}
