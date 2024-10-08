/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:43 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/08 14:54:38 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export_empty(t_program_data *data)
{
	t_env	*tmp;

	tmp = ft_env_sort(data->env);
	while (tmp)
	{
		printf("declare -x %s", tmp->var_name);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_export_var(char *arg, t_program_data *data)
{
	char	**split;
	t_env	*tmp;

	split = ft_split(arg, '=');
	if (ft_strchr(arg, '='))
	{
		tmp = malloc(sizeof(t_env));
		tmp->var_name = ft_strdup(split[0]);
		tmp->content = ft_strdup(split[1]);
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
	}
	else
	{
		tmp = malloc(sizeof(t_env));
		tmp->var_name = ft_strdup(arg);
		tmp->content = NULL;
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
	}
	ft_free_split(split);
}

void	ft_export(t_command *cmd, t_program_data *data)
{
	char	**split;
	int		i;

	if (!cmd->args)
		ft_export_empty(data);
	else
	{
		i = 0;
		split = ft_split(cmd->args, ' ');
		while (split[i])
		{
			ft_export_var(split[i], data);
			i++;
		}
		ft_free_split(split);
	}
}
