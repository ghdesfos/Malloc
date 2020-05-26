/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:57:40 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 19:19:37 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sarea	*create_mmap_area_small(void)
{
	t_sarea	*area;
	int		i;

	area = (t_sarea*)mmap(NULL, SBLOCKS * SMALL + HEADERSIZE, \
		PROT_READ | PROT_WRITE | PROT_EXEC, \
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	area->blocksize = SMALL;
	area->nbpages = 1 + (SBLOCKS * SMALL + HEADERSIZE - 1) \
							/ PAGESIZE;
	i = 0;
	while (i < SBLOCKS)
	{
		((area->bstatus)[i]).free = 1;
		((area->bstatus)[i]).nbblocks = 0;
		i++;
	}
	return (area);
}

int		check_if_enough_place_current_area_small(t_sarea *area, size_t size)
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
			return (1);
		i++;
	}
	return (0);
}

t_sarea	*get_right_mmap_area_small(size_t size)
{
	t_sarea	*area;
	t_sarea *tmp;

	if (g_areas.sarea == NULL)
		if ((g_areas.sarea = create_mmap_area_small()) == NULL)
			return (NULL);
	area = g_areas.sarea;
	while (area && check_if_enough_place_current_area_small(area, size) == 0)
		area = area->next;
	if (area == NULL)
	{
		if ((area = create_mmap_area_small()) == NULL)
			return (NULL);
		tmp = g_areas.sarea;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = area;
	}
	return (area);
}

void	*malloc_small(size_t size)
{
	t_sarea *area;

	if ((area = get_right_mmap_area_small(size)) == NULL)
		return (NULL);
	return (get_right_space_in_mmap_area_small(area, size));
}
