/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mmap_areas_sub.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:48:23 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/14 18:14:38 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_blocks_area_small(t_sarea *area, int width, int k)
{
	char	*tab;
	int		i;
	int		j;

	tab = "0123456789abcdef";
	b_printf("\n\n");
	i = -1;
	while (k && ++i < SBLOCKS)
	{
		j = -1;
		while (++j < SMALL)
		{
			if (j % width == 0 && j / width != 0)
				b_printf("\n");
			b_printf("%c%c ", tab[BL / 16], tab[BL % 16]);
		}
		b_printf("\n\n");
	}
}

void	print_blocks_area_medium(t_marea *area, int width, int k)
{
	char	*tab;
	int		i;
	int		j;

	tab = "0123456789abcdef";
	b_printf("\n\n");
	i = -1;
	while (k && ++i < MBLOCKS)
	{
		j = -1;
		while (++j < MEDIUM)
		{
			if (j % width == 0 && j / width != 0)
				b_printf("\n");
			b_printf("%c%c ", tab[BL / 16], tab[BL % 16]);
		}
		b_printf("\n\n");
	}
}
