/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzumaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:31:54 by suzumaki          #+#    #+#             */
/*   Updated: 2021/06/06 13:42:49 by suzumaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	char	*ptr;
	int		res;

	if (s == NULL)
		return (0);
	if (!s[0])
		return (0);
	res = 0;
	ptr = (char *)s;
	while (*ptr)
	{
		res++;
		ptr++;
	}
	return (res);
}
