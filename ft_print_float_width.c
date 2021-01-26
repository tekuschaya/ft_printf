/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_width.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 23:59:37 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 00:35:59 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_convert_exp(long double *tmp, long long int *base)
{
	int i;

	i = 0;
	if ((int)(*tmp))
	{
		while (*tmp > 10.0)
		{
			*tmp = *tmp / 10;
			i++;
		}
	}
	else
	{
		if (*tmp)
			while (*tmp < 1.0)
			{
				*tmp = *tmp * 10;
				i++;
			}
	}
	*base = (int)(*tmp);
	return (i);
}

void		ft_str_float_g(long double n, char *str, t_flag list,
			long long int base)
{
	int i;
	int len;

	len = ft_strlen(str);
	if (!list.octotorp)
		while (len-- && str[len] == '0')
			str[len] = '\0';
	if (base || (list.octotorp && !n))
	{
		i = (list.precision >= 0) ? list.precision -
		ft_len_number(base) : 6 - ft_len_number(base);
		i += (base < 0) ? 1 : 0;
		if (i >= 0 && i <= len)
			str[i] = '\0';
	}
	len = ft_strlen(str);
	if (!base && n != 0.0 && !list.precision)
	{
		while (len-- && str[len] == '0')
			str[len] = '\0';
	}
}

static int	ft_print_f(long long int base, t_flag list,
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
	return (count);
}

static int	ft_print_width_float(long long int base, t_flag list,
			char c, char *str)
{
	int i;
	int len;
	int point;

	i = (c == '\0') ? 0 : 1;
	point = (!list.octotorp && !ft_strlen(str)) ? 0 : 1;
	len = list.width - ft_len_number(base) - ft_strlen(str) - i - point;
	if (list.minus)
		return (ft_print_f(base, list, c, str) + ft_print_space(len));
	else
	{
		if (list.zero)
		{
			return (ft_putchar(c, i) + ft_print_zero(len) +
			ft_print_f(base, list, '\0', str));
		}
		else
			return (ft_print_space(len) + ft_print_f(base, list, c, str));
	}
}

int			ft_check_width_float(long double number, long long int base,
	char *str, t_flag list)
{
	int point;

	point = (!list.octotorp && !ft_strlen(str)) ? 0 : 1;
	if (list.width - ft_strlen(str) - ft_len_number(base) - point > 0)
	{
		if (number < 0.0 || 1 / number < 0)
			return (ft_print_width_float(base * -1, list, '-', str));
		else if (number >= 0.0 && list.plus)
			return (ft_print_width_float(base, list, '+', str));
		else if (list.space)
			return (ft_print_width_float(base, list, ' ', str));
		else
			return (ft_print_width_float(base, list, '\0', str));
	}
	if (list.plus && number >= 0.0 && 1 / number > 0)
		return (ft_print_f(base, list, '+', str));
	else if (number >= 0.0 && 1 / number > 0 && list.space)
		return (ft_print_f(base, list, ' ', str));
	else
	{
		return ((((number < 0.0 || 1 / number < 0) && !base) ?
		ft_putchar('-', 1) : 0) + ft_print_f(base, list, '\0', str));
	}
}
