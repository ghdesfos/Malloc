/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:34:57 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 21:25:30 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		show_alloc_mem_small(void)
{
	t_sarea	*area;
	int		i;
	int		nb_blocks;
	int		n;

	n = 0;
	area = g_areas.sarea;
	while (area)
	{
		b_printf("TINY : %p \n", area);
		i = -1;
		while (++i < SBLOCKS)
		{
			if ((nb_blocks = ((area->bstatus)[i]).nbblocks) > 0
					&& ((area->bstatus)[i]).free == 0)
			{
				b_printf("%p - %p : %d bytes\n", area->blocks[i], \
									area->blocks[i] + nb_blocks * SMALL - 1, \
									nb_blocks * SMALL);
				n += nb_blocks * SMALL;
			}
		}
		area = area->next;
	}
	return (n);
}

int		show_alloc_mem_medium(void)
{
	t_marea	*area;
	int		i;
	int		nb_blocks;
	int		n;

	n = 0;
	area = g_areas.marea;
	while (area)
	{
		b_printf("SMALL : %p\n", area);
		i = -1;
		while (++i < MBLOCKS)
		{
			if ((nb_blocks = ((area->bstatus)[i]).nbblocks) > 0
					&& ((area->bstatus)[i]).free == 0)
			{
				b_printf("%p - %p : %d bytes\n", area->blocks[i], \
									area->blocks[i] + nb_blocks * MEDIUM - 1, \
									nb_blocks * MEDIUM);
				n += nb_blocks * MEDIUM;
			}
		}
		area = area->next;
	}
	return (n);
}

int		show_alloc_mem_large(void)
{
	t_larea	*area;
	int		n;

	n = 0;
	area = g_areas.larea;
	while (area)
	{
		b_printf("LARGE : area\n");
		b_printf("%p - %p : %d bytes\n", area + HEADERSIZELARGE, \
									area + area->nbpages * PAGESIZE - 1, \
									area->nbpages * PAGESIZE - HEADERSIZELARGE);
		n += area->nbpages * PAGESIZE - HEADERSIZELARGE;
		area = area->next;
	}
	return (n);
}

void	show_alloc_mem(void)
{
	int n;

	n = 0;
	n += show_alloc_mem_small();
	n += show_alloc_mem_medium();
	n += show_alloc_mem_large();
	b_printf("Total : %d bytes\n", n);
}

void	show_alloc_mem_ex(void)
{
	show_alloc_mem();
	b_printf("\n");
	print_mmap_areas(100, 1, 0, 0);
}
