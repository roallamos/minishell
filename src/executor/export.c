/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:24:43 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/20 18:34:49 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  envp_size(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
        i++;
    return(i);
}

void    export(t_data *data, int pos)
{
    int size;
    
    size = envp_size(data->envp);
    if (data->args[pos + 1])
    {
        data->envp = ft_realloc(data->envp, size * sizeof(char *), (size + 1) * sizeof(char *));
        data->envp[size] = ft_strndup(data->args[pos + 1], ft_strlen(data->args[pos + 1]));
        data->envp[size +  1] = NULL;
    }
    i = 0;
    printf("size antes %i\n", size);
    size = envp_size(data->envp);
    printf("size despues %i\n", size);
   /* while(data->envp[i])
	{
		printf("despues %s\n", data->envp[i]);
		i++;
	}*/
}