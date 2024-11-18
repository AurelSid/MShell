/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/18 18:06:41 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_search_env_2(char *var)
{
	t_env	*tmp;

	tmp = ft_return_data()->env;
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

void	change_env(void)
{
	char	cwd[PATH_MAX];
	t_env	*curr;
	t_env	*old;

	curr = ft_search_env_2("PWD");
	old = ft_search_env_2("OLDPWD");
	if (curr)
	{
		if (old)
			old->content = curr->content;
		if (getcwd(cwd, sizeof(cwd)))
			curr->content = ft_strdup(cwd);
		else
			perror("pwd");
	}
	else if (old)
		old->content = ft_strdup("");
}

void	ft_cd(t_command *cmd)
{
	char	*tmp;
	char	**args;
	int		i;

	args = ft_split_args(cmd->args);
	tmp = args[0];
	if (!tmp || tmp[0] == '~')
	{
		tmp = "HOME";
		ft_search_env(&tmp);
	}
	if (ft_strcmp(tmp, "-") == 0)
	{
		tmp = "OLDPWD";
		ft_search_env(&tmp);
	}
	i = chdir(tmp);
	if (i == -1)
	{
		ft_return_data()->exit_status = 1;
		perror("cd");
	}
	ft_free_split(args);
	if (i != -1)
		change_env();
}
