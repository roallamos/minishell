/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:35:50 by migumore          #+#    #+#             */
/*   Updated: 2024/06/21 15:34:16 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_find_path(char *envp[])
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (envp[i] + 5);
			i++;
		}
	}
	return (NULL);
}
