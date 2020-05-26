/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 00:23:03 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 21:25:28 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		main(void)
{
	char *str1;
	char *str2;

	malloc(170);
	str1 = malloc(140);
	b_printf("STR1 %p\n", str1);
	malloc(350);
	str1[0] = 48;
	str1[1] = 49;
	str1[2] = 50;
	str1[3] = 51;
	str1 = (char*)realloc(str1, 900);
	realloc(str1, 350);
	malloc(700);
	str2 = malloc(140);
	realloc(str2, 70);
	b_printf("STR2 %p\n\n", str2);
	str2[0] = 55;
	str2[1] = 55;
	str2[2] = 55;
	show_alloc_mem_ex();
	return (0);
}
