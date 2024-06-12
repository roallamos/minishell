/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:52:46 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/24 16:08:21 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*cpy;
	unsigned long	n;

	n = ft_strlen(s1);
	cpy = (char *) malloc(n + 1);
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, s1, n + 1);
	return (cpy);
}
