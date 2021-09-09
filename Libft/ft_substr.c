/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzumaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:36:42 by suzumaki          #+#    #+#             */
/*   Updated: 2021/05/22 00:20:52 by suzumaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	n;

	n = 0;
	ptr = malloc((len + 1) * sizeof(char));
	if (!(ptr)
		|| !(s))
		return (NULL);
	while (n < len && start + n < ft_strlen(s))
	{
		ptr[n] = (char)s[start + n];
		++n;
	}
	ptr[n] = '\0';
	return (ptr);
}
