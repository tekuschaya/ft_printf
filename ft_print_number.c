/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:32:10 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 08:20:10 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_precision_number(long long int number, t_flag list, char c)
{
	int count;
	int i;

	i = (c == '\0') ? 0 : 1;
	if (list.width - list.precision - i > 0)
		if (list.minus)
		{
			count = ft_putchar(c, i) + ft_print_zero(list.precision -
			ft_len_number(number)) + ft_putnbr(number, 1);
			count += ft_print_space(list.width - list.precision - i);
		}
		else
		{
			count = ft_print_space(list.width - list.precision - i);
			count += ft_putchar(c, i);
			count += ft_print_zero(list.precision - ft_len_number(number));
			count += ft_putnbr(number, 1);
		}
	else
	{
		count = ft_putchar(c, i);
		count += ft_print_zero(list.precision - ft_len_number(number));
		count += ft_putnbr(number, 1);
	}
	return (count);
}

static int	ft_print_width_number(long long int number, t_flag list, char c)
{
	int count;
	int i;

	i = (c == '\0') ? 0 : 1;
	if (list.minus)
	{
		count = ft_putchar(c, i) + ft_putnbr(number, 1);
		count += ft_print_space(list.width - ft_len_number(number) - i);
	}
	else
	{
		if (list.zero && list.precision < 0)
		{
			count = ft_putchar(c, i);
			count += ft_print_zero(list.width - ft_len_number(number) - i);
			count += ft_putnbr(number, 1);
		}
		else
		{
			count = ft_print_space(list.width - ft_len_number(number) - i);
			count += ft_putchar(c, i) + ft_putnbr(number, 1);
		}
	}
	return (count);
}

static int	ft_check_flag_number(long long int number, t_flag list)
{
	if (list.precision >= ft_len_number(number))
	{
		if (number < 0)
			return (ft_print_precision_number(number * -1, list, '-'));
		else if (number >= 0 && list.plus)
			return (ft_print_precision_number(number, list, '+'));
		else if (list.space)
			return (ft_print_precision_number(number, list, ' '));
		else
			return (ft_print_precision_number(number, list, '\0'));
	}
	else if (list.width - ft_len_number(number) > 0)
	{
		if (number < 0)
			return (ft_print_width_number(number * -1, list, '-'));
		else if (number >= 0 && list.plus)
			return (ft_print_width_number(number, list, '+'));
		else if (list.space)
			return (ft_print_width_number(number, list, ' '));
		else
			return (ft_print_width_number(number, list, '\0'));
	}
	else
		return (0);
}

int			ft_print_number(long long int number, t_flag list)
{
	int count;

	if (!list.precision && !number)
	{
		if (list.plus)
		{
			if (list.minus && list.width)
				return (ft_putchar('+', 1) + ft_print_space(list.width - 1));
			else if (list.width)
				return (ft_print_space(list.width - 1) + ft_putchar('+', 1));
			else
				return (ft_putchar('+', 1));
		}
		return (ft_print_space(list.width));
	}
	if (!(count = ft_check_flag_number(number, list)))
	{
		if (list.plus && number >= 0)
			count = ft_putchar('+', 1) + ft_putnbr(number, 1);
		else if (number >= 0 && list.space)
			count = ft_putchar(' ', 1) + ft_putnbr(number, 1);
		else
			count = ft_putnbr(number, 1);
	}
	return (count);
}
