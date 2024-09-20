/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:17:00 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/20 17:10:37 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_search_env(char *var, t_program_data data)
{
	t_env	*tmp;

	tmp = data.env;
	while (tmp)
	{
		if ((ft_strcmp(var, tmp->var_name) == 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*				/!\	LEAKS IN STRJOIN	/!\				*/

void	ft_db_quotes(t_token *token, t_program_data data)
{
	char	*found;
	char	*start;
	char	*end;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(token->content, '$');
	if (!tmp)
		return ;
	while (tmp[i] != ' ')
		i++;
	found = ft_substr(tmp, 0, i);
	if (ft_search_env(found, data) != 0)
		return ;
	start = ft_substr(token->content, 0,
			ft_strlen(token->content) - ft_strlen(found));
	end = ft_strjoin(start, found);
	end = ft_strjoin(end, (tmp + i));
}
