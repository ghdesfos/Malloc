/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:22:31 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/02/15 21:18:14 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_PRINTF_H
# define B_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		format_handler_sub(va_list ap, char conv);
int		format_handler(va_list ap, char conv);
int		b_printf(const char *restrict format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
char	*ft_b_base(long n, int base);

#endif
