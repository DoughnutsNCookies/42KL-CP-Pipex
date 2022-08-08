/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:48:56 by schuah            #+#    #+#             */
/*   Updated: 2022/07/15 14:28:05 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

typedef struct s_flags
{
	int		num;
	int		neg;
	int		zero;
	int		dot;
	int		hash;
	int		spc;
	int		plus;
	int		width;
	int		prec;
	char	d;
}	t_flags;

void	print_with_format(char format, va_list *args, t_flags *flags, int *wc);
void	get_format(char format, va_list *args, t_flags *flags, int *wc);
int		ft_printf(const char *str, ...);
int		print_dupe(char c, int count);
void	print_with_flag(char *str, t_flags *flags, int *wc);
void	print_sf(char *str, t_flags *flags, int *wc);
void	print_cf(char c, t_flags *flags, int *wc);
void	default_flag(t_flags *flags);
int		is_format(char c);
int		get_space(const char *str, int *i);
void	get_flags(const char *str, int *i, t_flags *flags);
char	*ultoa_base(unsigned long n);
void	print_pf(unsigned long string_addr, t_flags *flags, int *wc);
void	print_pointer_space(t_flags *flags, int *wc, char *n);
void	print_stonf(char *n, t_flags *flags, int *wc);
void	print_number_space(t_flags *flags, int *wc, char *n);
void	check_splus(t_flags *flags, int *wc, int n);
void	print_nf(int n, t_flags *flags, int *wc);
int		get_uilen(unsigned int n);
char	*ft_uitoa(unsigned int n);
void	print_unf(unsigned int n, t_flags *glags, int *wc);
char	*ft_uitoa_base(unsigned int n, char *base);
void	print_hexstart(t_flags *flags, unsigned int n, int *len, char *base);
void	print_hf(unsigned int n, char *base, t_flags *flags, int *wc);

#endif
