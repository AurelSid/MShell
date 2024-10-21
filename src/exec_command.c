/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/21 14:17:40 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_built_ins(t_command *cmd)
{
	if (!ft_strcmp(cmd->name, "env") || !ft_strcmp(cmd->name, "echo")
		|| !ft_strcmp(cmd->name, "cd") || !ft_strcmp(cmd->name, "pwd")
		|| !ft_strcmp(cmd->name, "export") || !ft_strcmp(cmd->name, "unset")
		|| !ft_strcmp(cmd->name, "exit"))
		return (1);
	else
		return (0);
}
int	ft_exec_built_ins(t_command *cmd, t_program_data *data)
{
	if (!ft_strcmp(cmd->name, "env"))
		ft_env(*data);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd->args, cmd->options, *data);
	else if (!ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd->args);
	else if (!ft_strcmp(cmd->name, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->name, "export"))
		ft_export(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args);
	else
		return (1);
	return (0);
}
char	**ft_args_to_line(t_command *cmd)
{
	char	*tmp_line_1;
	char	*tmp_line_2;
	char	*tmp_line_3;
	char	*line;
	char	**line_split;
	int		i;

	i = 0;
	tmp_line_1 = ft_strjoin(cmd->name, " ");
	tmp_line_2 = ft_strjoin(tmp_line_1, cmd->options);
	free(tmp_line_1);
	tmp_line_3 = ft_strjoin(tmp_line_2, " ");
	free(tmp_line_3);
	line = ft_strjoin(tmp_line_2, cmd->args);
	free(tmp_line_2);
	line_split = ft_split(line, ' ');
	free(line);
	while (line_split[i])
		i++;
	return (line_split);
}

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
char	**ft_env_to_tab(t_program_data *data)
{
	t_env	*tmp_env;
	int		env_nmbr;
	char	**tab;
	int		i;
	char	*tmp;

	i = 0;
	env_nmbr = ft_count_envs(data);
	tab = malloc(sizeof(char *) * (env_nmbr + 1));
	tab[env_nmbr] = NULL;
	tmp_env = data->env;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->var_name, "=");
		if (tmp_env->content)
			tab[i] = ft_strjoin(tmp, tmp_env->content);
		else
			tab[i] = NULL;
		free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	return (tab);
}
int	ft_exec(t_command *cmd, char **env, t_program_data *data)
{
	char	**tab;

	(void)env;
	tab = ft_env_to_tab(data);
	signal(SIGINT, SIG_IGN);
	if (cmd->next == NULL)
		ft_exec_single_command(cmd, tab, data);
	else
	{
		if (cmd->next->input_fd > 0)
		{
			ft_exec_single_command(cmd, tab, data);
			setup_pipe_and_redirect();
		}
		else if (cmd->output_fd)
		{
			ft_exec_single_command(cmd, tab, data);
			setup_pipe_and_redirect();
		}
		else
			ft_exec_piped_command(cmd, tab, data);
	}
	ft_free_split(tab);
	signal(SIGINT, ft_handle_signals);
	return (0);
}
