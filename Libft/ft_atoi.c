/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzumaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:01:01 by suzumaki          #+#    #+#             */
/*   Updated: 2021/05/22 00:07:18 by suzumaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *ptr)
{
	int		res;
	int		cnt;
	int		sign;

	res = 0;
	cnt = 0;
	sign = 1;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n'
		|| *ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '-')
		sign = -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = res * 10 + *ptr - '0';
		if (res != 0)
			cnt++;
		ptr++;
	}
	if (cnt > 19)
		return ((-1 * sign - 1) / 2);
	return (res * sign);
}
