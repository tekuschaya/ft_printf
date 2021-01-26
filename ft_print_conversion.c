/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:30:03 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 08:18:16 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_len_number(long long int number)
{
	int len;

	len = 0;
	if (number <= 0)
		len = 1;
	while (number)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int		ft_len_u(unsigned long long int number)
{
	int len;

	len = 0;
	if (number == 0)
		len = 1;
	while (number)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int		ft_len_hex(unsigned long long int number)
{
	int len;

	len = 0;
	if (number == 0)
		len = 1;
	while (number)
	{
		number = number / 16;
		len++;
	}
	return (len);
}

void	ft_conversion_hex_low(unsigned long long int n, char *str, int len)
{
	str[len] = '\0';
	len--;
	if (!n)
		str[len] = '0';
	while (n)
	{
		if (n % 16 == 10)
			str[len] = 'a';
		else if (n % 16 == 11)
			str[len] = 'b';
		else if (n % 16 == 12)
			str[len] = 'c';
		else if (n % 16 == 13)
			str[len] = 'd';
		else if (n % 16 == 14)
			str[len] = 'e';
		else if (n % 16 == 15)
			str[len] = 'f';
		else
			str[len] = n % 16 + '0';
		n = n / 16;
		len--;
	}
}

void	ft_conversion_hex_up(unsigned long long int n, char *str, int len)
{
	str[len] = '\0';
	len--;
	if (!n)
		str[len] = '0';
	while (n)
	{
		if (n % 16 == 10)
			str[len] = 'A';
		else if (n % 16 == 11)
			str[len] = 'B';
		else if (n % 16 == 12)
			str[len] = 'C';
		else if (n % 16 == 13)
			str[len] = 'D';
		else if (n % 16 == 14)
			str[len] = 'E';
		else if (n % 16 == 15)
			str[len] = 'F';
		else
			str[len] = n % 16 + '0';
		n = n / 16;
		len--;
	}
}
