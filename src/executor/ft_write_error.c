/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:01:27 by migumore          #+#    #+#             */
/*   Updated: 2024/06/21 15:34:30 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_error(char *msg, char *arg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}
