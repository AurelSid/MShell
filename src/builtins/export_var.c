/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/13 15:32:41 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	supp_1(t_program_data *data, char *arg, char *var_name, t_env *tmp)
{
	tmp = ft_env_exist(arg, data);
	if (tmp)
		return (0);
	var_name = ft_strtrim_args(arg, 0, 0);
	if (!ft_valid_var(var_name))
	{
		write(2, " not a valid identifier\n", 24);
		data->exit_status = 1;
		return (0);
	}
	tmp = malloc(sizeof(t_env));
	tmp->var_name = var_name;
	tmp->content = NULL;
	tmp->next = NULL;
	ft_add_env(&data->env, tmp);
	return (1);
}

void	supp_3(t_env *tmp, char *var_name, char *content, t_program_data *data)
{
	if (content)
		ft_checkspchar(&content, data);
	tmp = ft_env_exist(var_name, data);
	var_name = ft_strtrim_args(var_name, 0, 0);
	content = ft_strtrim_args(content, 0, 0);
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

void	supp_5(t_program_data *data, char *arg, char **var_name, char **content)
{
	int	len;

	len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '='));
	if (len == 0)
		return ;
	*var_name = ft_substr(arg, 0, len);
	*content = ft_strdup(ft_strchr(arg, '=') + 1);
	if (*var_name)
		ft_checkspchar(var_name, data);
	if (!ft_valid_var(*var_name))
	{
		write(2, "  not a valid identifier\n", 25);
		data->exit_status = 1;
		free(*var_name);
		*var_name = NULL;
	}
}

void	ft_export_var(char *arg, t_program_data *data)
{
	char	*var_name;
	char	*content;
	t_env	*tmp;

	tmp = NULL;
	var_name = NULL;
	content = NULL;
	if (ft_strchr(arg, '='))
	{
		supp_5(data, arg, &var_name, &content);
		if (var_name == NULL)
			return ;
		supp_3(tmp, var_name, content, data);
	}
	else if (!supp_1(data, arg, var_name, tmp))
		return ;
}
