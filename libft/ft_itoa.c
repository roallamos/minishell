/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:34:32 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/28 17:37:52 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_str(char *str, long n, int size)
{
	if (n < 0)
		n = -n;
	if (n != 0)
	{
		str[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
		ft_str(str, n, size);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		size;
	int		t;
	char	*str;

	size = 0;
	t = n;
	if (n <= 0)
		size++;
	while (t != 0)
	{
		t = t / 10;
		size++;
	}
	str = ft_calloc(size + 1, 1);
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	str[size] = '\0';
	return (ft_str(str, n, size));
}

//int main(void)
//{
//	printf("%s", ft_itoa(10));
//	return (0);
//}
