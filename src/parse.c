/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:03:59 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/20 17:39:46 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    parse(t_data *data)
{
    int i;

    i = 0;
    while (data->args[i])
    {
        if (data->args[i][0] == '$')
            get_envp_value(data, &data->args[i][0], i);
        else if (!ft_strcmp(data->args[i], "export"))
            export(data, i);
        i++;
    }
}