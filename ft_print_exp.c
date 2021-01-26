/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:23:15 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/11 17:23:16 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_pow(int i)
{
	int count;

	count = 0;
	if (i)
	{
		if (i < 0)
		{
			count += ft_putchar('-', 1);
			i = i * -1;
		}
		else
			count += ft_putchar('+', 1);
		if (i < 10)
			count += ft_putchar('0', 1);
		count += ft_putnbr(i, 1);
	}
	else
	{
		count += ft_putchar('+', 1);
		count += ft_putstr("00", 1);
	}
	return (count);
}

static int	ft_print_e(long long int base, t_flag list,
			char c, char *str)
{
	int i;
	int count;
	int point;

	count = 0;
	i = (c == '\0') ? 0 : 1;
	point = (!list.octotorp && !ft_strlen(str)) ? 0 : 1;
	count += ft_putchar(c, i);
	count += ft_putnbr(base, 1);
	count += (point) ? ft_putchar('.', 1) : 0;
	count += ft_putstr(str, 1);
	count += ft_putchar('e', 1);
	count += ft_print_pow(list.pow);
	return (count);
}

static int	ft_print_width_exp(long long int base, t_flag list,
			char c, char *str)
{
	int i;
	int len;
	int point;
	int len_pow;

	len_pow = ft_len_number(list.pow);
	len_pow += (list.pow >= 0) ? 1 : 0;
	len_pow = (len_pow < 3) ? 3 : len_pow;
	i = (c == '\0') ? 0 : 1;
	point = (!list.octotorp && !ft_strlen(str)) ? 0 : 1;
	len = list.width - ft_len_number(base) - ft_strlen(str) -
	i - point - len_pow - 1;
	if (list.minus)
		return (ft_print_e(base, list, c, str) + ft_print_space(len));
	else
	{
		if (list.zero)
		{
			return (ft_putchar(c, i) + ft_print_zero(len) +
			ft_print_e(base, list, '\0', str));
		}
		else
			return (ft_print_space(len) + ft_print_e(base, list, c, str));
	}
}

int			ft_check_width_exp(long long int base, char *str, t_flag list)
{
	int point;
	int len_pow;

	len_pow = ft_len_number(list.pow);
	len_pow += (list.pow >= 0) ? 1 : 0;
	len_pow = (len_pow < 3) ? 3 : len_pow;
	point = (!list.octotorp && !ft_strlen(str)) ? 0 : 1;
	if (list.width - ft_strlen(str) - ft_len_number(base) -
		point - len_pow - 1 > 0)
	{
		if (base < 0)
			return (ft_print_width_exp(base * -1, list, '-', str));
		else if (base >= 0 && list.plus)
			return (ft_print_width_exp(base, list, '+', str));
		else if (base >= 0 && list.space)
			return (ft_print_width_exp(base, list, ' ', str));
		else
			return (ft_print_width_exp(base, list, '\0', str));
	}
	if (list.plus && base >= 0)
		return (ft_print_e(base, list, '+', str));
	else if (list.space && base >= 0)
		return (ft_print_e(base, list, ' ', str));
	else
		return (ft_print_e(base, list, '\0', str));
}

int			ft_print_exp(long double n, t_flag *list)
{
	long long int	base;
	long double		tmp;
	int				len;
	char			*str;
	int				count;

	base = 0;
	tmp = (n < 0) ? n * -1 : n;
	list->pow = ft_convert_exp(&tmp, &base);
	len = (list->precision < 0) ? 6 : list->precision;
	if (!(str = (char*)malloc(len + 1)))
		return (0);
	ft_str_float(tmp, str, len, &base);
	if (base == 10)
	{
		base = 1;
		list->pow += 1;
	}
	if (n < 0)
		base = base * -1;
	list->pow = (!(int)n) ? list->pow * -1 : list->pow;
	count = ft_check_width_exp(base, str, *list);
	free(str);
	return (count);
}
