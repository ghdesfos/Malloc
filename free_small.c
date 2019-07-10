/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:06:29 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:06:22 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sarea	*check_ptr_in_mmap_area_small(char *ptr)
{
	t_sarea	*area;
	int		mmap_size;

	area = g_areas.sarea;
	while (area)
	{
		mmap_size = area->nbpages * PAGESIZE;
		if ((void*)area <= (void*)ptr && (void*)ptr < (void*)area + mmap_size)
			return (area);
		area = area->next;
	}
	return (NULL);
}

int		free_blocks_in_mmap_area_small(t_sarea *area, int i)
{
	int n;
	int j;

	if ((n = ((area->bstatus)[i]).nbblocks) == 0
			|| ((area->bstatus)[i]).free == 1)
		return (0);
	j = 0;
	while (j < n)
	{
		((area->bstatus)[i + j]).free = 1;
		((area->bstatus)[i + j]).nbblocks = 0;
		j++;
	}
	return (1);
}

int		free_small(void *ptr)
{
	t_sarea	*area;
	int		i;

	area = check_ptr_in_mmap_area_small(ptr);
	if (area == NULL)
		return (0);
	i = 0;
	while (i < SBLOCKS)
	{
		if (ptr == (area->blocks)[i])
			return (free_blocks_in_mmap_area_small(area, i));
		i++;
	}
	return (0);
}
