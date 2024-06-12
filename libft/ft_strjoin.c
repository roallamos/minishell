/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:53:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/24 18:48:28 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	n;

	n = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc (n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	ft_strlcat(str, s2, n + 1);
	return (str);
}
