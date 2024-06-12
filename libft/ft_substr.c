/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:46:19 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/31 17:23:25 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	mem;

	mem = len;
	if (ft_strlen(s) <= start)
		return (ft_calloc(1, 1));
	if (mem > ft_strlen(s + start))
		mem = ft_strlen(s + start);
	sub = ft_calloc(mem + 1, 1);
	if (sub == 0)
		return (0);
	ft_strlcpy(sub, &s[start], mem + 1);
	return (sub);
}
