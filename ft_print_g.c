/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_g.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:37:47 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 09:38:37 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_str_exp_g(long double n, long long int *base,
				t_flag *list, char *str)
{
	int i;
	int len;

	len = ft_strlen(str);
	if (*base == 10)
	{
		*base = 1;
		list->pow += 1;
	}
	if (*base)
	{
		i = (list->precision >= 0) ? (list->precision -
		ft_len_number(*base)) : (6 - ft_len_number(*base));
		if (i >= 0 && i <= len)
		{
			str[i--] = '\0';
			if (i >= 0 && !list->octotorp)
				while (i >= 0 && str[i] == '0')
					str[i--] = '\0';
		}
	}
	if (n < 0)
		*base = *base * -1;
}

static int	ft_check_len_str(long long int base, long double rest, t_flag list)
{
	int i;

	i = 0;
	if (base && list.precision)
	{
		i = (list.precision > 0) ? (list.precision - ft_len_number(base)) :
		(6 - ft_len_number(base));
		i = (i < 0) ? 0 : i;
	}
	else if (!base && rest != 0.0 && list.precision)
	{
		while (!(int)(rest * 10))
		{
			rest = rest * 10;
			rest = rest - (int)rest;
			i++;
		}
		i += (list.precision > 0) ? list.precision : 6;
	}
	else
		i = (list.precision < 0) ? 6 : list.precision;
	return (i);
}

static int	ft_str_len_g(long double number, t_flag list)
{
	long double		rest;
	long long int	base;
	int				i;

	i = 0;
	if (number < 0)
		number = number * -1;
	base = (long long int)number;
	rest = number - base;
	if (!number && list.octotorp)
		return ((list.precision < 0) ? 5 : list.precision - 1);
	if ((rest == 0.0) || (base && !list.precision))
		return (0);
	if (!list.precision)
	{
		while (!(int)(rest))
		{
			rest = rest * 10;
			i++;
		}
	}
	else
		i = ft_check_len_str(base, rest, list);
	return (i);
}

static int	ft_check_exp(long double n, t_flag *list)
{
	long long int	base;
	long double		tmp;
	int				len;
	char			*str;
	int				count;

	count = 0;
	tmp = n;
	base = 0;
	if (tmp < 0)
		tmp = tmp * -1;
	list->pow = ft_convert_exp(&tmp, &base);
	list->pow = (!(int)n) ? list->pow * -1 : list->pow;
	len = (list->precision < 0) ? 5 : list->precision - 1;
	len = (len < 0) ? 0 : len;
	if (!(str = (char*)malloc(len + 1)))
		return (0);
	ft_str_float(tmp, str, len, &base);
	ft_str_exp_g(n, &base, list, str);
	if ((list->precision >= 0 && list->pow >= list->precision) ||
	list->pow < -4 || (list->precision < 0 && list->pow >= 6))
		count = ft_check_width_exp(base, str, *list);
	free(str);
	return (count);
}

int			ft_print_g(long double n, t_flag *list)
{
	long long int	base;
	int				len;
	char			*str;
	int				count;

	len = 0;
	count = 0;
	if (n != n)
		return (ft_print_nan("nan", *list));
	else if (n != 0.0 && n * 2 == n)
		return (ft_print_inf("inf", n, *list));
	if (n >= 10.0 || (n > 0 && n < 0.1) || (n < 0 && n > -0.1) || n <= -10.0)
		count = ft_check_exp(n, list);
	if (!count)
	{
		base = (long long int)n;
		len = ft_str_len_g(n, *list);
		if (!(str = (char*)malloc(len + 1)))
			return (0);
		ft_str_float(n, str, len, &base);
		ft_str_float_g(n, str, *list, base);
		count = ft_check_width_float(n, base, str, *list);
		free(str);
	}
	return (count);
}
