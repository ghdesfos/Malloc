/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_large.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:47:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/14 15:44:27 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*realloc_large(char *ptr, size_t size)
{
	t_larea			*area;
	char			*newptr;
	unsigned int	curr_area_size;
	unsigned int	j;

	area = check_ptr_in_mmap_area_large(ptr);
	if (area == NULL)
		return (NULL);
	curr_area_size = area->nbpages * PAGESIZE - HEADERSIZELARGE;
	if (curr_area_size >= size)
		return ((void*)ptr);
	newptr = (char*)malloc_large(size);
	j = 0;
	while (j < size)
	{
		newptr[j] = ptr[j];
		j++;
	}
	free_large(ptr);
	return ((void*)newptr);
}
