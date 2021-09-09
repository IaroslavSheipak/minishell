/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzumaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:09:46 by suzumaki          #+#    #+#             */
/*   Updated: 2021/05/22 00:16:21 by suzumaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcpy(char const *dst, char const *src, size_t dstsize)
{
	char			*cpy_dst;
	const char		*s;
	size_t			n;

	s = src;
	cpy_dst = (char *)dst;
	n = dstsize;
	if (n != 0)
		while (--n && *s != '\0')
			*cpy_dst++ = *s++;
	if (n == 0)
	{
		if (dstsize != 0)
			*cpy_dst = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
