/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printun_with_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:13:53 by schuah            #+#    #+#             */
/*   Updated: 2022/07/15 13:31:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_uilen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*output;
	int		len;

	len = get_uilen(n);
	output = malloc(sizeof(char) * (len + 1));
	if (output == NULL)
		return (NULL);
	output[len] = '\0';
	if (n == 0)
		output[0] = '0';
	while (n != 0)
	{
		output[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (output);
}

void	print_unf(unsigned int n, t_flags *flags, int *wc)
{
	char	*n_string;
	int		len;

	n_string = ft_uitoa(n);
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
	*wc += print_dupe('0', flags->prec - (int)ft_strlen(n_string)) + len;
	if (flags->dot == 1)
	{
		flags->d = ' ';
		if (flags->width == 0)
			flags->width = flags->prec;
		if (n_string[0] != '0' && (flags->prec < (int)ft_strlen(n_string)))
			flags->prec = (int)ft_strlen(n_string);
	}
	print_stonf(n_string, flags, wc);
	free(n_string);
}
