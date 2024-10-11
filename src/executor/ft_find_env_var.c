/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:35:50 by migumore          #+#    #+#             */
/*   Updated: 2024/10/11 14:47:12 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_find_env_var(char *envp[], char *var, int len)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], var, len) == 0)
				return (envp[i] + len);
			i++;
		}
	}
	return (NULL);
}
