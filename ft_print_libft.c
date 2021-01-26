/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:30:58 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/11 17:25:17 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi_print(const char *str, int *count)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] > 47 && str[i] < 58)
		res = res * 10 + str[i++] - 48;
	*count = *count + i;
	return (res);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*str1;

	i = 0;
	str1 = (char*)malloc(ft_strlen(str) + 1);
	if (str1)
	{
		while (str[i])
		{
			str1[i] = str[i];
			i++;
		}
		str1[i] = '\0';
		return (str1);
	}
	return (NULL);
}

int		ft_isdigit_print(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != '\0')
			i++;
	return (i);
}
