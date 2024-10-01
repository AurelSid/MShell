/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:45:11 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/01 13:06:36 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char *arg, t_program_data *data)
{
	t_env	*tmp;
	char	**split_arg;
	int		i;

	split_arg = ft_split(arg, ' ');
	i = 0;
	tmp = data->env;
	while (split_arg[i])
	{
		while (tmp)
		{
			if (strcmp(tmp->var_name, arg) == 0)
				break ;
			tmp = tmp->next;
		}
		i++;
	}
	i = 0;
	while (split_arg[i])
	{
		free(split_arg[i]);
		i++;
	}
	tmp->prev->next = tmp->next;
	free(tmp->var_name);
	free(tmp->content);
	free(split_arg);
	free(tmp);
	tmp = NULL;
}
