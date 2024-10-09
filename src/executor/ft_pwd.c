/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:18:29 by migumore          #+#    #+#             */
/*   Updated: 2024/10/09 20:26:36 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_pwd(t_data *data)
{
	if (data->pwd)
	{
		free(data->oldpwd);
		data->oldpwd = ft_strdup(data->pwd);
		free(data->pwd);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->oldpwd)
	{
		data->oldpwd = ft_find_env_var(data->env, "OLDPWD=", 7);
		if (!data->oldpwd)
			data->oldpwd = ft_strdup(data->pwd);
	}
}
