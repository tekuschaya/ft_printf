/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:30:36 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/11 17:57:35 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(char *str, t_flag list, char c, int remain)
{
	int count;

	count = 0;
	if (remain)
	{
		if (list.octotorp && str && str[0] != '0')
		{
			count += ft_putchar('0', 1);
			count += ft_putchar(c, 1);
		}
		count += ft_print_zero(remain);
		count += ft_putstr(str, 1);
	}
	else
	{
		if (list.octotorp && str && str[0] != '0')
		{
			count += ft_putchar('0', 1);
			count += ft_putchar(c, 1);
		}
		count += ft_putstr(str, 1);
	}
	return (count);
}

static int	ft_print_precision_hex(char *str, t_flag list, char c)
{
	int count;
	int remain;

	count = 0;
	remain = 0;
	if (list.octotorp && list.precision > ft_strlen(str) && str[0] != '0')
		remain = list.width - list.precision - 2;
	else if (list.precision > ft_strlen(str))
		remain = list.width - list.precision;
	if (remain > 0)
	{
		if (list.minus)
		{
			count += ft_hex(str, list, c, list.precision - ft_strlen(str));
			count += ft_print_space(remain);
		}
		else
		{
			count += ft_print_space(remain);
			count += ft_hex(str, list, c, list.precision - ft_strlen(str));
		}
	}
	else
		count += ft_hex(str, list, c, list.precision - ft_strlen(str));
	return (count);
}

static int	ft_print_width_hex(char *str, t_flag list, char c)
{
	int count;
	int remain;

	remain = 0;
	if (list.octotorp && list.width - ft_strlen(str) - 2 > 0 && str[0] != '0')
		remain = list.width - ft_strlen(str) - 2;
	else if (list.width - ft_strlen(str) > 0 && (str[0] == '0' ||
	(str[0] && !list.octotorp)))
		remain = list.width - ft_strlen(str);
	if (list.minus)
	{
		count = ft_hex(str, list, c, 0);
		count += ft_print_space(remain);
	}
	else
	{
		if (list.zero && list.precision < 0)
			count = ft_hex(str, list, c, remain);
		else
		{
			count = ft_print_space(remain);
			count += ft_hex(str, list, c, 0);
		}
	}
	return (count);
}

int			ft_print_h(unsigned long long int n, t_flag list, char c)
{
	int		len;
	int		count;
	char	*str;

	count = 0;
	if (!n && !list.precision)
		return (ft_print_space(list.width));
	len = ft_len_hex(n);
	if (!(str = (char*)malloc(len + 1)))
		return (0);
	if (c == 'X')
		ft_conversion_hex_up(n, str, len);
	if (c == 'x')
		ft_conversion_hex_low(n, str, len);
	if (list.precision > ft_strlen(str))
		count += ft_print_precision_hex(str, list, c);
	else if (list.width - ft_strlen(str) > 0)
		count += ft_print_width_hex(str, list, c);
	else if (n && list.octotorp)
		count += ft_hex(str, list, c, 0);
	else
		count += ft_putstr(str, 1);
	free(str);
	return (count);
}

int			ft_print_p(unsigned long long int n, t_flag list)
{
	char	*str;
	int		len;
	int		count;

	count = 0;
	if (!n && !list.precision)
		return (ft_print_width_hex("0x", list, list.width));
	len = ft_len_hex(n) + 2;
	if (!(str = (char*)malloc(len + 1)))
		return (0);
	ft_conversion_hex_low(n, str, len);
	str[0] = '0';
	str[1] = 'x';
	if (list.precision > ft_strlen(str))
		count += ft_print_precision_hex(str, list, 'x');
	else if (list.width - ft_strlen(str) > 0)
		count += ft_print_width_hex(str, list, 'x');
	else
		count += ft_putstr(str, 1);
	free(str);
	return (count);
}
