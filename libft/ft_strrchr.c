/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:02:27 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/22 14:50:39 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*t;

	i = 0;
	t = (char *) s;
	while (s[i])
		i++;
	if (!(char)c)
		return (&t[i]);
	while (i > 0)
	{
		if (t[i - 1] == (char)c)
			return (&t[i - 1]);
		i--;
	}
	return (0);
}
