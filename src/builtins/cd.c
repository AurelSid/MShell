/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/04 15:50:54 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_search_env_2(char *var, t_program_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if ((ft_strcmp(var, tmp->var_name) == 0))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_env(t_program_data *data)
{
	char	cwd[PATH_MAX];
	t_env	*curr;
	t_env	*old;

	curr = ft_search_env_2("PWD", data);
	old = ft_search_env_2("OLDPWD", data);
	free(old->content);
	old->content = curr->content;
	if (getcwd(cwd, sizeof(cwd)))
		curr->content = ft_strdup(cwd);
	else
		perror("pwd");
}

void	ft_cd(t_command *cmd, t_program_data *data)
{
	char	*tmp;
	char	**args;

	args = ft_split_args(cmd->args);
	tmp = args[0];
	if (!tmp || tmp[0] == '~')
	{
		tmp = "HOME";
		ft_search_env(&tmp, *data);
	}
	if (ft_strcmp(tmp, "-") == 0)
	{
		tmp = "OLDPWD";
		ft_search_env(&tmp, *data);
	}
	if (chdir(tmp) == -1)
	{
		data->exit_status = 1;
		perror("cd");
	}
	change_env(data);
}
