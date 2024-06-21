/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:38:22 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/21 14:20:24 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_spaces(const char *delim, char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(delim, (int)str[i]))
		i++;
	return (i);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;

	if (!str)
		str = last;
	if (!str)
		return (NULL);
	str += skip_spaces(delim, str);
	if (!*str)
	{
		last = NULL;
		return (NULL);
	}
	last = str;
	while (*last && !ft_strchr(delim, (int)*last))
		last++;
	if (!*last)
		last = NULL;
	else
	{
		*last = 0;
		last++;
	}
	return (str);
}
