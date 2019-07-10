/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:37:27 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 17:33:10 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	else if (size < MEDIUM + 1)
		return (malloc_small(size));
	else if (size < LARGE + 1)
		return (malloc_medium(size));
	else
		return (malloc_large(size));
}
