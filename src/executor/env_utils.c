/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:17:20 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/21 19:25:18 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	dup_env(t_data *data, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = env_size(env);
	data->env = ft_calloc(sizeof(char *), size + 1);
	if (!data->env)
		return ;
	while (i < size)
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
}
void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}