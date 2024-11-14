/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/14 13:27:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_opt(t_token **tmp, char *cmd_n, char **opt)
{
	char	*tmp_str;
	char	*free_tmp;

	while ((*tmp) && ((*tmp)->content[0] == '-' && (*tmp)->type == WORD))
	{
		if (ft_strcmp(cmd_n, "export"))
		{
			ft_checkspchar(&(*tmp)->content);
			tmp_str = (*tmp)->content;
		}
		free_tmp = *opt;
		*opt = ft_strjoin(free_tmp, (*tmp)->content);
		free(free_tmp);
		(*tmp) = (*tmp)->next;
		free_tmp = *opt;
		*opt = ft_strjoin(free_tmp, " ");
		free(free_tmp);
	}
	return (0);
}

int	ft_check_args(t_token **tmp, char *cmd_n, char **args)
{
	char	*tmp_str;
	char	*free_tmp;

	while ((*tmp) && (*tmp)->type == WORD)
	{
		if (ft_strcmp(cmd_n, "export"))
		{
			ft_checkspchar(&(*tmp)->content);
			tmp_str = (*tmp)->content;
		}
		*args = ft_strjoin_free(*args, (*tmp)->content);
		(*tmp) = (*tmp)->next;
		if (*args && (*args)[0])
		{
			free_tmp = *args;
			*args = ft_strjoin(free_tmp, " ");
			free(free_tmp);
		}
	}
	return (0);
}

void	ft_commands_fill_list(void)
{
	t_token	*tmp;
	char	*opt;
	char	*args;

	if (!ft_return_data()->token_top)
		return ;
	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	tmp = ft_return_data()->token_top;
	tmp = ft_commands_fill_list_r(tmp, &args, &opt);
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		ft_return_data()->token_top = tmp;
		ft_commands_fill_list();
	}
	if (opt)
		free(opt);
	if (args)
		free(args);
}
