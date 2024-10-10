/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:43 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/09 17:49:11 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_env_exist(char *var, t_program_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (strcmp(tmp->var_name, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

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

	if (ft_strchr(arg, '='))
	{
		split = ft_split(arg, '=');
		split[0] = ft_spchar(split[0], data);
		split[1] = ft_spchar(split[1], data);
		tmp = ft_env_exist(split[0], data);
		if (tmp)
		{
			free(tmp->content);
			tmp->content = ft_strdup(split[1]);
			return ;
		}
		tmp = malloc(sizeof(t_env));
		tmp->var_name = ft_strdup(split[0]);
		tmp->content = ft_strdup(split[1]);
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
		ft_free_split(split);
	}
	else
	{
		tmp = malloc(sizeof(t_env));
		tmp->var_name = ft_strdup(arg);
		tmp->content = NULL;
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
	}

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
