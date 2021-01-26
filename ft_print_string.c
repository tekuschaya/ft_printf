/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:32:53 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 09:04:04 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_width_str(char *str, t_flag list, int remain)
{
	int count;

	count = 0;
	if (remain > 0)
	{
		if (list.minus)
		{
			count += ft_putstr(str, 1);
			count += ft_print_space(remain);
		}
		else
		{
			if (list.zero)
				count += ft_print_zero(remain);
			else
				count += ft_print_space(remain);
			count += ft_putstr(str, 1);
		}
	}
	else
		count += ft_putstr(str, 1);
	return (count);
}

int			ft_print_string(char *str, t_flag list)
{
	int		i;
	int		count;
	char	*str1;

	if (!list.precision)
		return (ft_print_space(list.width));
	if (!str)
		str1 = ft_strdup("(null)");
	else
		str1 = ft_strdup(str);
	i = ft_strlen(str1);
	if (list.precision > 0 && list.precision < i)
		while (i >= list.precision)
			str1[i--] = '\0';
	count = ft_print_width_str(str1, list, list.width - ft_strlen(str1));
	free(str1);
	return (count);
}

int			ft_print_n(int *n, t_flag list)
{
	int *pointer;

	pointer = n;
	*pointer = list.count;
	return (0);
}

int			ft_print_char(int symbol, t_flag list)
{
	int count;

	count = 0;
	if (list.width)
	{
		if (list.minus)
		{
			count += ft_putchar(symbol, 1);
			count += ft_print_space(list.width - 1);
		}
		else
		{
			if (list.zero)
				count += ft_print_zero(list.width - 1);
			else
				count += ft_print_space(list.width - 1);
			count += ft_putchar(symbol, 1);
		}
	}
	else
		count += ft_putchar(symbol, 1);
	return (count);
}
