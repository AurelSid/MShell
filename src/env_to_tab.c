/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:06 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/05 13:37:49 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_envs(t_program_data *data)
{
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = data->env;
	while (tmp_env)
	{
		i++;
		tmp_env = tmp_env->next;
	}
	return (i);
}

char	**ft_env_to_tab_init(char **tab, t_program_data *data)
{
	int		env_nmbr;

	env_nmbr = ft_count_envs(data);
	tab = malloc(sizeof(char *) * (env_nmbr + 1));
	if (!tab)
		return (NULL);
	tab[env_nmbr] = NULL;
	return (tab);
}

void	ft_env_free_tab(int i, char ***tab, char **tmp)
{
	free(*tmp);
	while (i > 0)
	{
		i--;
		free((*tab)[i]);
	}
	free((*tab));
}

char	**ft_env_to_tab(char **tab, t_program_data *data)
{
	t_env	*tmp_env;
	int		i;
	char	*tmp;
	char	*combined_str;

	i = 0;
	tab = ft_env_to_tab_init(tab, data);
	tmp_env = data->env;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->var_name, "=");
		if (!tmp)
			return (ft_env_free_tab(i, &tab, &tmp), NULL);
		if (tmp_env->content)
			combined_str = ft_strjoin(tmp, tmp_env->content);
		else
			combined_str = ft_strdup(tmp);
		if (combined_str)
			tab[i++] = combined_str;
		else
			return (ft_env_free_tab(i, &tab, &tmp), NULL);
		free(tmp);
		tmp_env = tmp_env->next;
	}
	return (tab);
}
