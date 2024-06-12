/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:18:08 by rodralva          #+#    #+#             */
/*   Updated: 2024/02/19 18:18:54 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;
	size_t	n;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	n = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc (n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	ft_strlcat(str, s2, n + 1);
	free ((char *)s1);
	return (str);
}
