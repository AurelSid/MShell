/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:46 by asideris          #+#    #+#             */
/*   Updated: 2024/10/07 18:59:52 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_free(t_program_data *data, char *exit_msg)
{
	fprintf(stderr,"%s",exit_msg);

	ft_clean_tokens(data);
	ft_clean_commands(data);
	
}