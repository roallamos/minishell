/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:34:05 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/29 19:24:07 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*temp;
	char		*ret;
	size_t		n;

	n = ft_strlen(s1);
	temp = s1 + n - 1;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (*s1 && ft_strchr(set, *temp))
		temp--;
	ret = ft_substr(s1, 0, temp - s1 + 1);
	return (ret);
}
