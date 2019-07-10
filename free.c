/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:37:49 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 16:14:28 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free(void *ptr)
{
	char	*ptrbis;

	if (!ptr)
		return ;
	ptrbis = (char*)ptr;
	if (free_small(ptrbis) == 0)
		if (free_medium(ptrbis) == 0)
			free_large(ptrbis);
}
