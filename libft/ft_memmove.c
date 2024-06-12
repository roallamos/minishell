/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:45:18 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/22 14:42:51 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*des;

	sr = (unsigned char *)src;
	des = (unsigned char *)dst;
	i = 0;
	if (sr == 0 && des == 0)
		return (0);
	if (sr > des)
	{
		while (i < len)
		{
			des[i] = sr[i];
			i++;
		}
	}
	while (len > i)
	{
		des[len - 1] = sr[len - 1];
		len--;
	}
	return (des);
}
