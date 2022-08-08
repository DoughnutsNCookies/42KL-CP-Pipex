/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:11:03 by schuah            #+#    #+#             */
/*   Updated: 2022/07/04 20:18:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	check_max(int value)
{
	if (value == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	value;
	int	number;
	int	counter;

	i = 0;
	value = 1;
	number = 0;
	counter = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			value = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (counter > 10 || number > 2147483647)
			return (check_max(value));
		number = (number * 10) + (str[i++] - 48);
		counter++;
	}
	return (number * value);
}
