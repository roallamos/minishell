/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:48 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/22 14:50:29 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	char	*hay;

	i = 0;
	j = 0;
	hay = (char *) haystack;
	if (needle[j] == '\0')
		return (hay);
	while (hay[i] && i < len)
	{
		if (hay[i] == needle[j])
		{
			while (hay[i + j] == needle[j] && i + j < len)
			{
				j++;
				if (needle[j] == '\0')
					return (&hay[i]);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
