/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:01:27 by migumore          #+#    #+#             */
/*   Updated: 2024/10/16 01:39:50 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_error(char *msg, char *arg)
{
	ft_putstr_fd(msg, STDERR);
	ft_putendl_fd(arg, STDERR);
}

void	write_n_change_status(char *msg, int status)
{
	printf("%s", msg);
	g_exit_status = status;
}
