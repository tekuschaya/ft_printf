/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:32:10 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/11 18:59:29 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_putnbr_u(unsigned long long int n, int fd)
{
	int len;

	len = ft_len_u(n);
	if (n > 9)
	{
		ft_putnbr(n / 10, fd);
		ft_putchar(n % 10 + '0', fd);
	}
	else
		ft_putchar(n + '0', fd);
	return (len);
}

static int	ft_print_precision_number(unsigned long long int number,
			t_flag list)
{
	int count;

	count = 0;
	if (list.width - list.precision > 0)
		if (list.minus)
		{
			count += ft_print_zero(list.precision -
			ft_len_u(number)) + ft_putnbr_u(number, 1);
			count += ft_print_space(list.width - list.precision);
		}
		else
		{
			count += ft_print_space(list.width - list.precision);
			count += ft_print_zero(list.precision - ft_len_u(number));
			count += ft_putnbr_u(number, 1);
		}
	else
	{
		count += ft_print_zero(list.precision - ft_len_u(number));
		count += ft_putnbr_u(number, 1);
	}
	return (count);
}

static int	ft_print_width_number(unsigned long long int number,
			t_flag list)
{
	int count;

	count = 0;
	if (list.minus)
	{
		count += ft_putnbr_u(number, 1);
		count += ft_print_space(list.width - ft_len_u(number));
	}
	else
	{
		if (list.zero && list.precision < 0)
		{
			count += ft_print_zero(list.width - ft_len_u(number));
			count += ft_putnbr_u(number, 1);
		}
		else
		{
			count = ft_print_space(list.width - ft_len_u(number));
			count += ft_putnbr_u(number, 1);
		}
	}
	return (count);
}

int			ft_print_u(unsigned long long int number, t_flag list)
{
	int count;

	count = 0;
	if (!list.precision && !number)
		return (ft_print_space(list.width));
	if (list.precision >= ft_len_u(number))
		count = ft_print_precision_number(number, list);
	else if (list.width - ft_len_u(number) > 0)
		count = ft_print_width_number(number, list);
	else
		count = ft_putnbr_u(number, 1);
	return (count);
}
