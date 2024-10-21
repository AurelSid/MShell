/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:45:11 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/21 14:57:19 by asideris         ###   ########.fr       */
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
	if (strcmp(split_arg[0], "PATH") == 0)
	{
		data->exit_status = 0;
		return ;
	}
	while (split_arg[i])
	{
		while (tmp)
		{
			if (strcmp(tmp->var_name, arg) == 0)
			{
				tmp->prev->next = tmp->next;
				free(tmp->var_name);
				free(tmp->content);
				free(tmp);
				tmp = NULL;
				break ;
			}
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
