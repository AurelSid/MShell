/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:43 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/21 18:28:17 by vpelc            ###   ########.fr       */
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
	char	*var_name;
	char	*content;
	int		len;
	t_env	*tmp;

	var_name = NULL;
	if (ft_strchr(arg, '='))
	{
		len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '='));
		if (len == 0)
			return ;		/*  ----> ERROR */
		var_name = ft_substr(arg, 0, len);
		content = ft_strdup(ft_strchr(arg, '=') + 1);

  		if (var_name)
			ft_checkspchar(&var_name, 1);
		if (content)
			ft_checkspchar(&content, 1);
		tmp = ft_env_exist(var_name, data);
		if (tmp)
		{
			free(tmp->content);
			tmp->content = content;
			return ;
		}
		tmp = malloc(sizeof(t_env));
		tmp->var_name = var_name;
		tmp->content = content;
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
	}

	else
	{
		tmp = ft_env_exist(arg, data);
		if (tmp)
			return ;
		tmp = malloc(sizeof(t_env));
		tmp->var_name = ft_strdup(arg);
		tmp->content = NULL;
		tmp->next = NULL;
		ft_add_env(&data->env, tmp);
	}
	//ft_print_env(*data);
}

void	ft_export(t_command *cmd, t_program_data *data)
{
	char	**split;
	int		i;

	if (!cmd->args[0])
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
