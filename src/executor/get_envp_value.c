/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:17:20 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/20 16:31:52 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    get_envp_value(t_data *data, char *s, int pos)
{
    int i;
    int len;
    int len_e;

    i = 0;
    len = ft_strlen(s) - 1;
    len_e = len + 1;
    while (data->envp[i] && ft_strncmp(data->envp[i], s + 1, len))
        i++;;
    len = ft_strlen(data->envp[i]) - len;
    free(s);
    data->args[pos] = ft_strndup(&data->envp[i][len_e], len);
}