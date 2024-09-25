/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:43 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/25 17:47:44 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_program_data *data, char *arg)
{
	t_env	*tmp;
	char	**split;
	int		i;
	int		len;

	if (!arg)
	{
		tmp = data->env;
		while (tmp)
		{
			printf("declare -x %s", tmp->var_name);
			if (tmp->content)
				printf("=\"%s\"", tmp->content);
			printf("\n");
			tmp = tmp->next;
		}
	}
	i = 0;
	split = ft_split(arg, ' ');
	while (split[i])
	{
		if (ft_strchr(split[i], '='))
		{
			tmp = malloc(sizeof(t_env));
			len = ft_strlen(split[i]) - ft_strlen(ft_strchr(split[i], '='));
			tmp->var_name = ft_substr(split[i], 0, len);
			tmp->content = ft_strdup(ft_strchr(split[i], '=') + 1);
			tmp->next = NULL;
			ft_add_env(&data->env, tmp);
		}
		else
		{
			tmp = malloc(sizeof(t_env));
			tmp->var_name = ft_strdup(split[i]);
			tmp->content = NULL;
			tmp->next = NULL;
			ft_add_env(&data->env, tmp);
		}
		i++;
	}
}
