/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:33:38 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/11 20:27:57 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_type(const char *s, va_list argv, t_flag *list, int *i)
{
	*i = *i + 1;
	if (*s == 'c')
		list->count += ft_print_char(va_arg(argv, int), *list);
	else if (*s == 's')
		list->count += ft_print_string(va_arg(argv, char*), *list);
	else if (*s == 'd' || *s == 'i')
		list->count += ft_print_number(va_arg(argv, int), *list);
	else if (*s == 'x' || *s == 'X')
		list->count += ft_print_h(va_arg(argv, unsigned int), *list, *s);
	else if (*s == 'u')
		list->count += ft_print_u(va_arg(argv, unsigned int), *list);
	else if (*s == 'p')
		list->count += ft_print_p(va_arg(argv, unsigned long long), *list);
	else if (*s == 'l' || *s == 'h')
		list->count += ft_check_size(s, argv, list, i);
	else if (*s == 'f')
		list->count += ft_print_float(va_arg(argv, double), *list);
	else if (*s == 'n')
		ft_print_n(va_arg(argv, int*), *list);
	else if (*s == 'e')
		list->count += ft_print_exp(va_arg(argv, double), list);
	else if (*s == 'g')
		list->count += ft_print_g(va_arg(argv, double), list);
	else
		list->count += ft_print_char(*s, *list);
}

void	ft_check_t_flag(t_flag *list, const char *str, int *i)
{
	list->minus = 0;
	list->plus = 0;
	list->space = 0;
	list->octotorp = 0;
	list->zero = 0;
	list->width = 0;
	list->pow = 0;
	list->precision = -1;
	while (*str == '-' || *str == '+' || *str == ' ' ||
			*str == '#' || *str == '0')
	{
		if (*str == '-')
			list->minus = 1;
		else if (*str == '+')
			list->plus = 1;
		else if (*str == '0')
			list->zero = 1;
		else if (*str == ' ')
			list->space = 1;
		else if (*str == '#')
			list->octotorp = 1;
		str++;
		*i = *i + 1;
	}
}

int		ft_check_width(t_flag *list, const char *str, va_list argv, int *i)
{
	if (*str == '*')
	{
		list->width = va_arg(argv, int);
		*i = *i + 1;
	}
	else if (ft_isdigit_print(*str))
	{
		list->width = ft_atoi_print(str, i);
	}
	if (list->width < 0)
	{
		list->width = (list->width * -1);
		list->minus = 1;
	}
	return (0);
}

int		ft_check_presicion(t_flag *list, const char *str, va_list argv, int *i)
{
	int len;

	len = 0;
	while (*str == '.')
	{
		str++;
		*i = *i + 1;
		if (*str == '*')
		{
			list->precision = va_arg(argv, int);
			*i = *i + 1;
			str++;
		}
		else if (ft_isdigit_print(*str))
		{
			list->precision = ft_atoi_print(str, &len);
			str += len;
			*i = *i + len;
		}
		else
			list->precision = 0;
	}
	return (0);
}

int		ft_printf(const char *str, ...)
{
	int		i;
	t_flag	list;
	va_list	argv;

	list.count = 0;
	i = 0;
	va_start(argv, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			ft_check_t_flag(&list, &str[i], &i);
			ft_check_width(&list, &str[i], argv, &i);
			ft_check_presicion(&list, &str[i], argv, &i);
			if (str[i])
				ft_check_type(&str[i], argv, &list, &i);
		}
		else if (str[i] != '%')
			list.count += ft_putchar(str[i++], 1);
		else
			break ;
	}
	va_end(argv);
	return (list.count);
}
