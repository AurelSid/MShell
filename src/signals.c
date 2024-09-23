/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:52:59 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/23 16:09:05 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ft_catch_signals(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		printf("new prompt\n");
		exit(0);
	}
}

void	ft_init_signals(void)
{
	struct sigaction	sig_c;
	struct sigaction	sig_bsl;

	sig_c.sa_sigaction = ft_catch_signals;
	sigemptyset(&sig_c.sa_mask);
	sig_c.sa_flags = 0;
	sigaction(SIGINT, &sig_c, NULL);
	sig_bsl.sa_sigaction = SIG_IGN;
	sigemptyset(&sig_bsl.sa_mask);
	sig_bsl.sa_flags = 0;
	sig action(SIGQUIT, &sig_bsl, NULL);
}*/
void	ft_handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//printf("new prompt\n");
		//exit(0);
	}
}
