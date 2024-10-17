/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:47:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/17 17:48:13 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	check_overflow(long long *result, int digit, int sign)
{
	if (*result > (LLONG_MAX - digit) / 10)
	{
		if (sign == 1)
			*result = LLONG_MAX;
		else
			*result = LLONG_MIN;
		return (1);
	}
	return (0);
}

static void	advanced_spaces_n_sign(const char **p, int *sign, int *subtract)
{
	while (ft_isspace(**p))
		(*p)++;
	if (**p == '-')
	{
		*sign = -1;
		(*p)++;
		*subtract = 1;
	}
	else if (**p == '+')
		(*p)++;
}

int	ft_atoll(const char *str, long long *result)
{
	int			sign;
	int			subtract;
	int			digit;
	const char	*p = str;

	*result = 0;
	sign = 1;
	subtract = 0;
	advanced_spaces_n_sign(&p, &sign, &subtract);
	while (*p >= '0' && *p <= '9')
	{
		digit = *p - '0';
		p++;
		if (subtract && (!(p) || !ft_isdigit(*p)))
			digit--;
		if (check_overflow(result, digit, sign))
			return (1);
		*result = *result * 10 + digit;
	}
	*result *= sign;
	return (0);
}
