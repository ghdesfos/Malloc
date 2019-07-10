/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:39:28 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:18:00 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		shorten_alloc_area_small(t_sarea *area, int i, int nb)
{
	int oldnbblocks;
	int j;

	oldnbblocks = ((area->bstatus)[i]).nbblocks;
	j = 0;
	while (j < oldnbblocks)
	{
		((area->bstatus)[i + j]).free = 1;
		((area->bstatus)[i + j]).nbblocks = 0;
		j++;
	}
	actual_change_curr_area_to_new_size_small(area, i, nb);
	return (1);
}

int		actual_change_curr_area_to_new_size_small(t_sarea *area, int i, int nb)
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
	return (1);
}

int		set_curr_alloc_area_to_new_size_small(t_sarea *area, int i, \
													size_t size)
{
	int nb;
	int j;

	if (((area->bstatus)[i]).nbblocks == 0
		|| ((area->bstatus)[i]).free == 1)
		return (-1);
	nb = (1 + (size - 1) / SMALL);
	if (nb <= ((area->bstatus)[i]).nbblocks)
		return (shorten_alloc_area_small(area, i, nb));
	j = ((area->bstatus)[i]).nbblocks;
	while (i + j < SBLOCKS && j < 5 && j < nb)
	{
		if (((area->bstatus)[i + j]).free == 1)
			j++;
		else
			break ;
	}
	if (j == nb)
		return (actual_change_curr_area_to_new_size_small(area, i, nb));
	return (0);
}

void	*transfer_alloc_to_new_area_small(char *ptr, size_t size)
{
	char			*newptr;
	unsigned int	j;

	newptr = (char*)malloc(size);
	j = 0;
	while (j < size)
	{
		newptr[j] = ptr[j];
		j++;
	}
	free_small(ptr);
	return ((void*)newptr);
}

void	*realloc_small(char *ptr, size_t size)
{
	t_sarea	*area;
	int		i;
	int		ret;

	area = check_ptr_in_mmap_area_small(ptr);
	if (area == NULL)
		return (NULL);
	i = 0;
	while (i < SBLOCKS)
	{
		if ((unsigned char*)ptr == (area->blocks)[i])
		{
			if ((ret = set_curr_alloc_area_to_new_size_small(area, i, size)) \
						== 1)
				return ((void*)ptr);
			else if (ret == 0)
				return (transfer_alloc_to_new_area_small(ptr, size));
		}
		i++;
	}
	return (NULL);
}
