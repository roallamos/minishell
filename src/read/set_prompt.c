/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:25:46 by migumore          #+#    #+#             */
/*   Updated: 2024/10/10 17:12:05 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_prompt(t_data *data)
{
	data->prompt = ft_strjoin(BOLD_GREEN, "minishell");
	if (!data->prompt)
		return ;
	data->prompt = ft_strjoin_free(data->prompt, BOLD_WHITE"$ "RESET);
	if (!data->prompt)
		return ;
}
