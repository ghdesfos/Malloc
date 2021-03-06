/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:29:22 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 21:18:10 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int		format_handler_sub(va_list ap, char conv)
{
	int		i;
	char	*str;

	i = 0;
	if (conv == 'o')
	{
		str = ft_b_base(va_arg(ap, unsigned int), 8);
		i = ft_putstr(str);
		free(str);
	}
	else if (conv == 'u')
	{
		str = ft_b_base(va_arg(ap, unsigned int), 10);
		i = ft_putstr(str);
		free(str);
	}
	else if (conv == 'x')
	{
		str = ft_b_base(va_arg(ap, unsigned int), 16);
		i = ft_putstr(str);
		free(str);
	}
	return (i);
}

int		format_handler(va_list ap, char conv)
{
	int		i;
	char	*str;

	i = 0;
	if (conv == 's')
		i = ft_putstr(va_arg(ap, char*));
	else if (conv == 'c')
		i = ft_putchar(va_arg(ap, int));
	else if (conv == 'd' || conv == 'i')
		i = ft_putnbr(va_arg(ap, int));
	else if (conv == '%')
		i = ft_putchar('%');
	else if (conv == 'p')
	{
		str = ft_b_base(va_arg(ap, unsigned long), 16);
		i = ft_putchar('0') + ft_putchar('x') + ft_putstr(str);
		free(str);
	}
	else
		i = format_handler_sub(ap, conv);
	return (i);
}

int		b_printf(const char *restrict format, ...)
{
	va_list		ap;
	int			output;
	int			i;

	output = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			output += ft_putchar(format[i]);
		}
		else
		{
			i++;
			output += format_handler(ap, format[i]);
		}
		i++;
	}
	va_end(ap);
	return (output);
}
