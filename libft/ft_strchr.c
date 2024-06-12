/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:35:58 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/22 14:45:13 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*t;

	i = 0;
	t = (char *) s;
	while (t[i])
	{
		if (t[i] == (char) c)
			return (&t[i]);
		i++;
	}
	if (!(char) c)
		return (&t[i]);
	return (0);
}
