/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:25:30 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:06:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_larea	*create_mmap_area_large(size_t size)
{
	t_larea *area;
	t_larea *tmp;

	area = (t_larea*)mmap(NULL, size + HEADERSIZELARGE, PROT_READ \
	| PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	area->blocksize = size;
	area->nbpages = 1 + (size + HEADERSIZELARGE - 1) / PAGESIZE;
	if (g_areas.larea == NULL)
		g_areas.larea = area;
	else
	{
		tmp = g_areas.larea;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = area;
	}
	return (area);
}

void	*malloc_large(size_t size)
{
	t_larea *area;

	area = create_mmap_area_large(size);
	return ((void*)((char*)area + HEADERSIZELARGE));
}
