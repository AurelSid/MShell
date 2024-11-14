/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/14 13:52:41 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_valid_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*ft_env_exist(char *var)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (strcmp(tmp->var_name, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_export_empty(void)
{
	t_env	*tmp;

	tmp = ft_env_sort(g_data.env);
	while (tmp)
	{
		printf("declare -x %s", tmp->var_name);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_export(t_command *cmd)
{
	char			**split;
	int		i;

	if (cmd->options[0])
		return ((void)printf("invalid option\n"));
	if (!cmd->args[0])
		ft_export_empty();
	else
	{
		split = ft_split_args_2(cmd->args);
		ft_export_trim(&split);
		i = -1;
		while (split[++i])
		{
			if (!ft_strcmp(split[i], "="))
			{
				write(2, " not a valid identifier\n", 24);
				g_data.exit_status = 1;
				continue ;
			}
			ft_export_var(split[i]);
		}
		ft_free_split(split);
	}
}
