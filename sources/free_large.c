/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:28:26 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:07:24 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_larea	*check_ptr_in_mmap_area_large(char *ptr)
{
	t_larea *area;

	area = g_areas.larea;
	while (area)
	{
		if ((char*)area + HEADERSIZELARGE == ptr)
			return (area);
		area = area->next;
	}
	return (NULL);
}

void	remove_freed_mmap_area_from_list_large(char *ptr)
{
	t_larea *area;
	t_larea *tmp;

	if (g_areas.larea == NULL)
		return ;
	area = check_ptr_in_mmap_area_large(ptr);
	if (area == g_areas.larea)
		g_areas.larea = area->next;
	else
	{
		tmp = g_areas.larea;
		while (tmp->next && (char*)(tmp->next) + HEADERSIZELARGE != ptr)
			tmp = tmp->next;
		if (tmp->next)
			tmp->next = tmp->next->next;
	}
}

int		free_large(char *ptr)
{
	t_larea *area;

	area = check_ptr_in_mmap_area_large(ptr);
	if (area == NULL)
		return (0);
	remove_freed_mmap_area_from_list_large(ptr);
	if (munmap((void*)(ptr - HEADERSIZELARGE), \
				((t_larea*)area)->nbpages * PAGESIZE) == -1)
	{
		write(2, "problem with munmap\n", 20);
		return (0);
	}
	return (1);
}
