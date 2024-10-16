/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:24:32 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/14 13:10:56 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_init_data(t_program_data *data)
{
	data->token_top = NULL;
	data->command_top = NULL;
	data->env = NULL;
	data->exit_status = 0;
	data->exit_status = 0;
	return (0);
}
