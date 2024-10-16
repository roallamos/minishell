/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:44 by migumore          #+#    #+#             */
/*   Updated: 2024/10/16 15:47:11 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <limits.h>

static void	atoll_aux(const char *p, int *sign)
{
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\f'
		|| *p == '\v')
		p++;
	if (*p == '-')
	{
		*sign = -1;
		p++;
	}
	else if (*p == '+')
		p++;
}

static int	ft_atoll(const char *str, long long *result)
{
	int			sign;
	int			digit;
	const char	*p = str;

	*result = 0;
	sign = 1;
	atoll_aux(p, &sign);
	while (*p >= '0' && *p <= '9')
	{
		digit = *p - '0';
		if (*result > (LLONG_MAX - digit) / 10)
		{
			if (sign == 1)
				*result = LLONG_MAX;
			else
				*result = LLONG_MIN;
			return (1);
		}
		*result = *result * 10 + digit;
		p++;
	}
	*result *= sign;
	return (0);
}

static void	check_args_aux(t_data *data, int *j, int i)
{
	*j = 0;
	if (data->list->args[i][*j] == '+' || data->list->args[i][*j] == '-')
		(*j)++;
	while (ft_isdigit(data->list->args[i][*j]))
		(*j)++;
}

static int	check_args(t_data *data)
{
	int			i;
	int			j;
	long long	nb;

	i = 0;
	while (data->list && data->list->args[i])
	{
		if (i == 1)
		{
			check_args_aux(data, &j, i);
			if (data->list->args[i][j] || ft_atoll(data->list->args[i], &nb))
			{
				write_error("minishell: exit: numeric argument required: ",
					data->list->args[i]);
				return (2);
			}
		}
		else if (i > 1)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		i++;
	}
	return (0);
}

int	do_exit(t_data *data, int in_child)
{
	int	exit_status;

	if (!in_child)
		printf("exit\n");
	exit_status = check_args(data);
	if (!exit_status && data->list && data->list->args[1])
		exit_status = ft_atoi(data->list->args[1]);
	else if (exit_status == 0)
		exit_status = g_exit_status;
	else if (exit_status == 1)
	{
		g_exit_status = exit_status;
		return (1);
	}
	free(data->prompt);
	ft_free_array((void **)data->env);
	ft_free_array((void **)data->path);
	ft_free_lst(data);
	exit(exit_status);
}
