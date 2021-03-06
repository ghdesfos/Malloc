/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:34:02 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 21:18:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int		ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

int		ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int		ft_putnbr(int n)
{
	int tmp;
	int i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		i++;
	}
	tmp = n;
	while (tmp /= 10)
		i++;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
	return (i + 1);
}

char	*ft_b_base(long n, int base)
{
	char	*str;
	char	*tab;
	long	tmp;
	int		len;

	tab = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (0);
	tmp = n;
	len = 1;
	while (tmp /= base)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len] = 0;
	while (len > 0)
	{
		str[len - 1] = tab[n % base];
		n /= base;
		len--;
	}
	return (str);
}
