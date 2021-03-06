/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:38:47 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/09 09:39:03 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

int	check_error(long num, const char *str, int negative, int i)
{
	long	real_num;

	real_num = num * negative;
	if (!ft_isdigit(str[i])
		|| (negative == 1 && real_num > INT_MAX)
		|| (negative == -1 && real_num < INT_MIN))
		return (-1);
	return (0);
}

unsigned int	ft_atoui(const char *str, bool *err)
{
	int		i;
	int		negative;
	long	num;

	i = 0;
	num = 0;
	negative = 1;
	if (str[0] == '\0')
		*err = true;
	if (str[i] == '-')
	{
		*err = true;
		negative = -1, i++;
	}
	while (str[i] != '\0')
	{
		num *= 10;
		num += str[i] - '0';
		if (check_error(num, str, negative, i) == -1)
			*err = true;
		i++;
	}
	return ((int)num * negative);
}
