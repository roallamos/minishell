/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:42:58 by rodralva          #+#    #+#             */
/*   Updated: 2024/02/19 12:05:35 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	array = (char *) malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, (count * size));
	return (array);
}
