/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:45:11 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/12 16:27:12 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	supp(t_env *prev, t_env *tmp)
{
	if (prev == NULL)
		g_data.env = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->var_name);
	free(tmp->content);
	free(tmp);
	tmp = NULL;
}

void	ft_unset(t_command *cmd)
{
	t_env	*tmp;
	t_env	*prev;
	char	**split_arg;
	int		i;

	split_arg = ft_split(cmd->args, ' ');
	i = 0;
	while (split_arg[i])
	{
		tmp = g_data.env;
		prev = NULL;
		while (tmp)
		{
			if (strcmp(tmp->var_name, split_arg[i]) == 0)
			{
				supp(prev, tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	ft_free_split(split_arg);
}
