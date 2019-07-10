/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_medium.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:01:01 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:05:32 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_marea	*create_mmap_area_medium(void)
{
	t_marea	*area;
	int		i;

	area = (t_marea*)mmap(NULL, MBLOCKS * MEDIUM + HEADERSIZE, \
		PROT_READ | PROT_WRITE | PROT_EXEC, \
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	area->blocksize = MEDIUM;
	area->nbpages = 1 + (MBLOCKS * MEDIUM + HEADERSIZE - 1) \
							/ PAGESIZE;
	i = 0;
	while (i < MBLOCKS)
	{
		((area->bstatus)[i]).free = 1;
		((area->bstatus)[i]).nbblocks = 0;
		i++;
	}
	return (area);
}

int		check_if_enough_place_current_area_medium(t_marea *area, size_t size)
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
			return (1);
		i++;
	}
	return (0);
}

t_marea	*get_right_mmap_area_medium(size_t size)
{
	t_marea	*area;
	t_marea *tmp;

	if (g_areas.marea == NULL)
		if ((g_areas.marea = create_mmap_area_medium()) == NULL)
			return (NULL);
	area = g_areas.marea;
	while (area && check_if_enough_place_current_area_medium(area, size) == 0)
		area = area->next;
	if (area == NULL)
	{
		if ((area = create_mmap_area_medium()) == NULL)
			return (NULL);
		tmp = g_areas.marea;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = area;
	}
	return (area);
}

void	*malloc_medium(size_t size)
{
	t_marea *area;

	if ((area = get_right_mmap_area_medium(size)) == NULL)
		return (NULL);
	return (get_right_space_in_mmap_area_medium(area, size));
}
