/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:15 by odhazzar          #+#    #+#             */
/*   Updated: 2020/06/13 09:03:47 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_lst
{
	int minus;
	int plus;
	int space;
	int octotorp;
	int zero;
	int width;
	int precision;
	int count;
	int pow;
}				t_flag;

int				ft_printf(const char *str, ...);
int				ft_check_presicion(t_flag *list, const char *str,
				va_list argv, int *i);
int				ft_check_width(t_flag *list, const char *str,
				va_list argv, int *i);
void			ft_check_t_flag(t_flag *list, const char *str,
				int *i);
void			ft_check_type(const char *s, va_list argv,
				t_flag *list, int *i);
int				ft_check_size(const char *s, va_list argv,
				t_flag *list, int *i);
int				ft_len_number(long long int number);
int				ft_len_hex(unsigned long long int number);
void			ft_conversion_hex_low(unsigned long long int n,
				char *str, int len);
void			ft_conversion_hex_up(unsigned long long int n,
				char *str, int len);
int				ft_print_h(unsigned long long int n, t_flag list, char c);
int				ft_print_p(unsigned long long int n, t_flag list);
int				ft_strlen(char *str);
int				ft_isdigit_print(int c);
char			*ft_strdup(char *str);
int				ft_atoi_print(const char *str, int *count);
int				ft_print_number(long long int number, t_flag list);
int				ft_print_string(char *str, t_flag list);
int				ft_print_char(int symbol, t_flag list);
int				ft_print_space(int count);
int				ft_print_zero(int count);
int				ft_putnbr(long long int n, int fd);
int				ft_putstr(char *s, int fd);
int				ft_putchar(char c, int fd);
int				ft_print_float(long double number, t_flag list);
int				ft_check_width_float(long double number, long long int base,
				char *str, t_flag list);
void			ft_str_float(long double number, char *str, int len,
				long long int *base);
void			ft_rounding(char *str, int i, long long int *base);
int				ft_print_u(unsigned long long int number, t_flag list);
int				ft_len_u(unsigned long long int number);
int				ft_putnbr_u(unsigned long long int n, int fd);
int				ft_print_exp(long double n, t_flag *list);
int				ft_print_n(int *n, t_flag list);
int				ft_print_g(long double n, t_flag *list);
void			ft_str_float_g(long double n, char *str, t_flag list,
				long long int base);
int				ft_check_width_exp(long long int base, char *str, t_flag list);
int				ft_convert_exp(long double *tmp, long long int *base);
int				ft_print_inf(char *str, long double number, t_flag list);
int				ft_print_nan(char *str, t_flag list);

#endif
