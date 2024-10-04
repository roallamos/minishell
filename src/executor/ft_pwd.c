/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:18:29 by migumore          #+#    #+#             */
/*   Updated: 2024/10/04 15:41:12 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_find_pwd(char *env[])
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				return (env[i] + 4);
			i++;
		}
	}
	return (NULL);
}
