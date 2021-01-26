/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 00:02:23 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/12 08:26:59 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_nan(char *str, t_flag list)
{
	int count;
	int remain;

	remain = list.width - 3;
	if (remain > 0)
	{
		if (list.minus)
		{
			count = ft_putstr(str, 1);
			count += ft_print_space(remain);
		}
		else
		{
			count = ft_print_space(remain);
			count += ft_putstr(str, 1);
		}
	}
	else
		count = ft_putstr(str, 1);
	return (count);
}

int		ft_print_inf(char *str, long double number, t_flag list)
{
	int remain;
	int sign;

	sign = (number < 0.0 || list.plus) ? 1 : 0;
	remain = list.width - 3 - sign;
	if (remain > 0)
	{
		if (list.minus)
			return (((number < 0.0) ? ft_putchar('-', 1) : 0) +
			((number >= 0.0 && list.plus) ? ft_putchar('+', 1) : 0) +
			ft_putstr(str, 1) + ft_print_space(remain));
		else
			return (ft_print_space(remain) + ((number < 0.0) ?
			ft_putchar('-', 1) : 0) + ((number >= 0.0 && list.plus) ?
			ft_putchar('+', 1) : 0) + ft_putstr(str, 1));
	}
	if (list.plus && number >= 0.0)
		return (ft_putchar('+', 1) + ft_putstr(str, 1));
	else if (number >= 0.0 && list.space)
		return (ft_putchar(' ', 1) + ft_putstr(str, 1));
	else if (number < 0.0)
		return (ft_putchar('-', 1) + ft_putstr(str, 1));
	else
		return (ft_putstr(str, 1));
}

void	ft_rounding(char *str, int i, long long int *base)
{
	if (i > 0)
	{
		i--;
		while (i >= 0)
		{
			if (str[i] == '9')
				str[i--] = '0';
			else
			{
				str[i] += 1;
				break ;
			}
		}
		if (i == -1 && str[0] == '0')
		{
			if (*base < 0)
				*base -= 1;
			else
				*base += 1;
		}
	}
	else
		*base = (*base < 0) ? *base - 1 : *base + 1;
}

void	ft_str_float(long double number, char *str, int len,
			long long int *base)
{
	long double	rest;
	int			tmp;
	int			i;

	i = 0;
	if (number < 0)
		number = number * -1;
	rest = number - (long long int)number;
	while (i < len)
	{
		rest = rest * 10;
		tmp = rest;
		str[i++] = tmp + '0';
		rest = rest - tmp;
	}
	tmp = rest * 10;
	if (tmp > 4 && rest * 10 - tmp > 0.0)
		ft_rounding(str, i, base);
	str[i] = '\0';
}

int		ft_print_float(long double number, t_flag list)
{
	long long int	base;
	int				len;
	char			*str;
	int				count;

	base = (long long int)number;
	len = (list.precision < 0) ? 6 : list.precision;
	if (number != number)
		return (ft_print_nan("nan", list));
	else if (number != 0.0 && number * 2 == number)
		return (ft_print_inf("inf", number, list));
	else if (!(str = (char*)malloc(len + 1)))
		return (0);
	ft_str_float(number, str, len, &base);
	count = ft_check_width_float(number, base, str, list);
	free(str);
	return (count);
}
