/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:07:40 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:06:35 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_marea	*check_ptr_in_mmap_area_medium(char *ptr)
{
	t_marea	*area;
	int		mmap_size;

	area = g_areas.marea;
	while (area)
	{
		mmap_size = area->nbpages * PAGESIZE;
		if ((void*)area <= (void*)ptr && (void*)ptr < (void*)area + mmap_size)
			return (area);
		area = area->next;
	}
	return (NULL);
}

int		free_blocks_in_mmap_area_medium(t_marea *area, int i)
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

int		free_medium(void *ptr)
{
	t_marea	*area;
	int		i;

	area = check_ptr_in_mmap_area_medium(ptr);
	if (area == NULL)
		return (0);
	i = 0;
	while (i < MBLOCKS)
	{
		if (ptr == (area->blocks)[i])
			return (free_blocks_in_mmap_area_medium(area, i));
		i++;
	}
	return (0);
}
