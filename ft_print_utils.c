/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:33:15 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 09:37:02 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int fd)
{
	if (fd && write(fd, &c, 1))
		return (1);
	return (0);
}

int	ft_putstr(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putnbr(long long int n, int fd)
{
	int len;

	len = ft_len_number(n);
	if (n < 0)
		ft_putchar('-', fd);
	if (n / 10 != 0)
		ft_putnbr((n < 0) ? -1 * (n / 10) : (n / 10), fd);
	ft_putchar((n < 0) ? -1 * (n % 10) + '0' : n % 10 + '0', fd);
	return (len);
}

int	ft_print_zero(int count)
{
	int i;

	i = 0;
	while (i++ < count)
		ft_putchar('0', 1);
	return (count);
}

int	ft_print_space(int count)
{
	int i;

	i = 0;
	while (i++ < count)
		ft_putchar(' ', 1);
	return (count);
}
