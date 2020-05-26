/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:37:39 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:14:37 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	check_which_type_mmap_ptr_is_in(char *ptr)
{
	if (check_ptr_in_mmap_area_small(ptr) != NULL)
		return ('s');
	else if (check_ptr_in_mmap_area_medium(ptr) != NULL)
		return ('m');
	else if (check_ptr_in_mmap_area_large(ptr) != NULL)
		return ('l');
	else
		return ('e');
}

void	*realloc(void *ptr, size_t size)
{
	char *ptrbis;
	char type_mmap;

	if (size <= 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	ptrbis = (char*)ptr;
	type_mmap = check_which_type_mmap_ptr_is_in(ptrbis);
	if (type_mmap == 's')
		return (realloc_small(ptrbis, size));
	else if (type_mmap == 'm')
		return (realloc_medium(ptrbis, size));
	else if (type_mmap == 'l')
		return (realloc_large(ptrbis, size));
	else if (type_mmap == 'e')
		return (NULL);
	return (NULL);
}
