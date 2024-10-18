/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:31:19 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/17 18:24:24 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		sleep(1);
		rl_replace_line("", 0);
		sleep(1);
		rl_on_new_line();
		sleep(1);
		printf("\n");
		sleep(1);
		rl_redisplay();
		sleep(1);
	}
}

void	ft_handle_signals_child(int signal)
{
	if (signal == SIGINT)
	{
		sleep(1);
		rl_replace_line("", 0);
		sleep(1);
		rl_on_new_line();
		sleep(1);
		printf("\n");
		sleep(1);
		rl_redisplay();
		sleep(1);
		exit(130);
	}
}
