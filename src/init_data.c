/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:24:32 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/12 16:28:37 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_init_data(void)
{
	g_data.token_top = NULL;
	g_data.command_top = NULL;
	g_data.env = NULL;
	g_data.exit_status = 0;
	g_data.child = 0;
	g_data.sig_int = 0;
	return (0);
}
