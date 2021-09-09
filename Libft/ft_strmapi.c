/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzumaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:18:59 by suzumaki          #+#    #+#             */
/*   Updated: 2021/05/22 00:17:03 by suzumaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	char	*res;
	size_t	n;

	n = 0;
	if (!(s && f))
		return (NULL);
	res = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(res))
		return (NULL);
	while (n < ft_strlen(s))
	{
		res[n] = f(n, s[n]);
		n++;
	}
	res[n] = '\0';
	return (res);
}
