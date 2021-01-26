/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:32:35 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 10:07:58 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_size_ll(const char *s, va_list argv, t_flag *list, int *i)
{
	int count;
	int j;

	count = 0;
	j = 1;
	*i = *i + 1;
	if (s[j] == 'd' || s[j] == 'i')
		count = ft_print_number(va_arg(argv, long long int), *list);
	else if (s[j] == 'u')
		count = ft_print_u(va_arg(argv, unsigned long long int), *list);
	else if (s[j] == 'c')
		count = ft_print_char(va_arg(argv, wchar_t), *list);
	else if (s[j] == 'x' || s[j] == 'X')
		count = ft_print_h(va_arg(argv, unsigned long long int), *list, s[j]);
	else
		*i = *i - 1;
	return (count);
}

static int	ft_check_size_l(const char *s, va_list argv, t_flag *list, int *i)
{
	int count;
	int j;

	count = 0;
	j = 1;
	*i = *i + 1;
	if (s[j] != 'l')
	{
		if (s[j] == 'd' || s[j] == 'i')
			count = ft_print_number(va_arg(argv, long int), *list);
		else if (s[j] == 'u')
			count = ft_print_u(va_arg(argv, unsigned long int), *list);
		else if (s[j] == 'x' || s[j] == 'X')
			count = ft_print_h(va_arg(argv, unsigned long int), *list, s[j]);
		else
			*i = *i - 1;
	}
	else
	{
		count = ft_check_size_ll(s + 1, argv, list, i);
	}
	return (count);
}

static int	ft_check_size_hh(const char *s, va_list argv, t_flag *list, int *i)
{
	int count;
	int j;

	count = 0;
	j = 1;
	*i = *i + 1;
	if (s[j] == 'd' || s[j] == 'i')
		count = ft_print_number((signed char)va_arg(argv, int), *list);
	else if (s[j] == 'u')
		count = ft_print_u((unsigned char)va_arg(argv, unsigned int),
		*list);
	else if (s[j] == 'x' || s[j] == 'X')
		count = ft_print_h((unsigned char)va_arg(argv, unsigned int),
		*list, s[j]);
	else
		*i = *i - 1;
	return (count);
}

static int	ft_check_size_h(const char *s, va_list argv, t_flag *list, int *i)
{
	int count;
	int j;

	count = 0;
	j = 1;
	*i = *i + 1;
	if (s[j] != 'h')
	{
		if (s[j] == 'd' || s[j] == 'i')
			count = ft_print_number((short int)va_arg(argv, int), *list);
		else if (s[j] == 'u')
			count = ft_print_u((unsigned short int)va_arg(argv,
			unsigned int), *list);
		else if (s[j] == 'x' || s[j] == 'X')
			count = ft_print_h((unsigned short int)va_arg(argv, unsigned int),
			*list, s[j]);
		else
			*i = *i - 1;
	}
	else
	{
		count = ft_check_size_hh(s + 1, argv, list, i);
	}
	return (count);
}

int			ft_check_size(const char *s, va_list argv, t_flag *list, int *i)
{
	int count;

	count = 0;
	if (*s == 'l')
		count = ft_check_size_l(s, argv, list, i);
	else if (*s == 'h')
		count = ft_check_size_h(s, argv, list, i);
	return (count);
}
