/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:26:03 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/09 19:57:11 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || !src)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	while (i + 1 < dstsize && *src)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	if (src_len + i >= dstsize && i < dstsize)
		return (i + ft_strlen(src));
	else if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	else
		return (ft_strlen(dst));
}
