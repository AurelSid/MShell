/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:24:32 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/14 13:30:17 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_program_data	*ft_return_data(void)
{
	static t_program_data	data;

	return (&data);
}

int	ft_init_data(void)
{
	ft_return_data()->token_top = NULL;
	ft_return_data()->command_top = NULL;
	ft_return_data()->env = NULL;
	ft_return_data()->exit_status = 0;
	ft_return_data()->child = 0;
	ft_return_data()->sig_int = 0;
	return (0);
}
