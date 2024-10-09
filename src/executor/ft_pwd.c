/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:18:29 by migumore          #+#    #+#             */
/*   Updated: 2024/10/09 19:39:37 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = ft_find_env_var(data->env, "OLDPWD=", 7);
	if (!data->oldpwd)
		data->oldpwd = ft_strdup(data->pwd);
}
