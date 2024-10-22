/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:45:11 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/22 13:54:23 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_command *cmd, t_program_data *data)
{
	t_env	*tmp;
	t_env	*prev;
	char	**split_arg;
	int		i;

	split_arg = ft_split_args(cmd->args);
	i = 0;
	while (split_arg[i])
	{
		tmp = data->env;
		prev = NULL;
		while (tmp)
		{
			if (strcmp(tmp->var_name, split_arg[i]) == 0)
			{
				if (prev == NULL)
					data->env = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp->var_name);
				free(tmp->content);
				free(tmp);
				tmp = NULL;
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	ft_free_split(split_arg);
}

/* 	i = 0;
	while (split_arg[i])
	{
		free(split_arg[i]);
		i++;
	}
	free(split_arg);
	tmp->prev->next = tmp->next;
	free(tmp->var_name);
	free(tmp->content);
	free(tmp);
	tmp = NULL; */
