/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printh_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:18:02 by schuah            #+#    #+#             */
/*   Updated: 2022/07/15 14:34:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uitoa_base(unsigned int n, char *base)
{
	int				i;
	char			*output;
	unsigned int	temp;

	i = 1;
	temp = n;
	while (temp >= 16 && (temp / 16) > 0 && ++i)
		temp /= 16;
	output = malloc(sizeof(char) * (i + 1));
	output[i] = '\0';
	while (n >= 16)
	{
		output[--i] = base[n % 16];
		n /= 16;
	}
	output[--i] = base[n % 16];
	return (output);
}

void	print_hexstart(t_flags *flags, unsigned int n, int *wc, char *base)
{
	if (flags->hash == 1 && n > 0)
	{
		*wc += 2;
		if (base[10] == 'a')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
	}
	if (flags->dot == 1)
		flags->d = ' ';
}

void	print_hf(unsigned int n, char *base, t_flags *flags, int *wc)
{
	char	*n_string;
	int		len;

	n_string = ft_uitoa_base(n, base);
	len = 0;
	if (flags->neg == 0 && flags->dot == 1 && flags->prec > 0
		&& (flags->width > flags->prec))
	{
		if ((int)ft_strlen(n_string) > flags->prec)
			len += print_dupe(' ', flags->width - (int)ft_strlen(n_string));
		else
			len += print_dupe(' ', flags->width - flags->prec);
		flags->width -= len;
	}
	print_hexstart(flags, n, wc, base);
	*wc += print_dupe('0', flags->prec - (int)ft_strlen(n_string)) + len;
	if (flags->dot == 1)
	{
		if (flags->width == 0)
			flags->width = flags->prec;
		if (n_string[0] != '0' && (flags->prec < (int)ft_strlen(n_string)))
			flags->prec = (int)ft_strlen(n_string);
	}
	print_stonf(n_string, flags, wc);
	free(n_string);
}
