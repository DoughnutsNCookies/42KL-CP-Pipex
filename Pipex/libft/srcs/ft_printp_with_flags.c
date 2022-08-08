/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp_with_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:13:18 by schuah            #+#    #+#             */
/*   Updated: 2022/07/16 22:51:30 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ultoa_base(unsigned long n)
{
	unsigned long	temp;
	char			*output;
	int				count;

	count = 3;
	temp = n;
	while (temp >= 16 && (temp / 16) && ++count)
		temp /= 16;
	temp = n;
	output = malloc(sizeof(char) * (count + 1));
	if (output == NULL)
		return (NULL);
	output[count] = '\0';
	output[0] = '0';
	output[1] = 'x';
	while (temp >= 16)
	{
		--count;
		output[count] = "0123456789abcdef"[temp % 16];
		temp /= 16;
	}
	output[--count] = "0123456789abcdef"[temp % 16];
	return (output);
}

void	print_pf(unsigned long string_addr, t_flags *flags, int *wc)
{
	char	*n;
	int		len;

	n = ultoa_base(string_addr);
	len = 0;
	if (flags->neg == 0 && (flags->dot == 1 && flags->prec == 1)
		&& flags->width > flags->prec)
	{
		if (flags->prec < (int)ft_strlen(n))
			len += print_dupe(' ', flags->width - (int)ft_strlen(n));
		else
			len += print_dupe(' ', flags->width - flags->prec);
		flags->width -= len;
	}
	*wc += len;
	wc += print_dupe('0', flags->prec - (int)ft_strlen(n));
	if (flags->dot == 1)
		flags->d = ' ';
	if (flags->dot == 1 && flags->width == 0)
		flags->width = flags->prec;
	if (flags->dot == 1 && (flags->prec < (int)ft_strlen(n)) && n[0 != '0'])
		flags->prec = (int)ft_strlen(n);
	print_stonf(n, flags, wc);
	free(n);
}
