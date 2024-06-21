/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:45:52 by migumore          #+#    #+#             */
/*   Updated: 2024/06/21 17:00:57 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new;

	len = ft_strnlen(s, n);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	return (ft_memcpy(new, s, len));
}
