/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mmap_areas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:31:43 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/15 17:48:33 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_mmap_area_small(t_sarea *area, int width, int i, int k)
{
	while (area)
	{
		b_printf("SMALL\nNumber Pages: %d\nNext Block? %s\n", \
			area->nbpages, (area->next) ? "Yes" : "No");
		i = -1;
		while (++i < SBLOCKS)
		{
			if (i % 10 == 0 && i / 10 != 0)
				b_printf("\n");
			b_printf("%d[%d] ", (BS.free == 1) ? 0 : 1, (BS.nbblocks));
		}
		print_blocks_area_small(area, width, k);
		b_printf("\n----------------------------------------------\n\n");
		area = area->next;
	}
}

void	print_mmap_area_medium(t_marea *area, int width, int i, int k)
{
	while (area)
	{
		b_printf("MEDIUM\nNumber Pages: %d\nNext Block? %s\n", \
			area->nbpages, (area->next) ? "Yes" : "No");
		i = -1;
		while (++i < MBLOCKS)
		{
			if (i % 10 == 0 && i / 10 != 0)
				b_printf("\n");
			b_printf("%d[%d] ", (BS.free) ? 0 : 1, (BS.nbblocks));
		}
		print_blocks_area_medium(area, width, k);
		b_printf("\n----------------------------------------------\n\n");
		area = area->next;
	}
}

void	print_mmap_area_large(t_larea *area, int width, int i, int k)
{
	char	*tab;
	char	ch;

	tab = "0123456789abcdef";
	while (area)
	{
		b_printf("LARGE\nNumber Pages: %d\nNext Block? %s\n", \
			area->nbpages, (area->next) ? "Yes" : "No");
		b_printf("\n\n");
		i = -1;
		while (k && ++i < area->nbpages * PAGESIZE - HEADERSIZELARGE)
		{
			if (i % width == 0 && i / width != 0)
				b_printf("\n");
			ch = ((char*)area + HEADERSIZELARGE)[i];
			b_printf("%c%c ", tab[ch / 16], tab[ch % 16]);
		}
		b_printf("\n\n----------------------------------------------\n\n");
		area = area->next;
	}
}

void	print_mmap_areas(int width, int a, int b, int c)
{
	int		i;
	t_sarea	*sarea;
	t_marea	*marea;
	t_larea	*larea;

	i = -1;
	sarea = g_areas.sarea;
	marea = g_areas.marea;
	larea = g_areas.larea;
	b_printf("HERE ARE THE MMAP AREA(S):\n\n");
	print_mmap_area_small(sarea, width, i, a);
	print_mmap_area_medium(marea, width, i, b);
	print_mmap_area_large(larea, width, i, c);
}
