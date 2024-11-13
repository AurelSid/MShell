/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/13 14:49:55 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_redirects(int *i)
{
	if (g_data.input[*i] == '>')
	{
		if (g_data.input[*i + 1] == '>')
		{
			ft_new_token(">>", REDIRECT_APPEND);
			(*i)++;
		}
		else
			ft_new_token(">", REDIRECT_OUT);
	}
	else if (g_data.input[*i] == '<')
	{
		if (g_data.input[*i + 1] == '<')
		{
			ft_new_token("<<", REDIRECT_HEREDOC);
			(*i)++;
		}
		else
			ft_new_token("<", REDIRECT_IN);
	}
	else if (g_data.input[*i] == '|')
		ft_new_token("|", PIPE);
	else
		return (0);
	return (1);
}

int	process_word(int *i)
{
	int		j;
	char	*tmp_name;

	j = *i;
	while (g_data.input[j] && (g_data.input[j] != ' ' && g_data.input[j] != '>'
			&& g_data.input[j] != '<' && g_data.input[j] != '|'))
	{
		if (g_data.input[j] == '\'' || g_data.input[j] == '\"')
			j += ft_handle_quotes(g_data.input, j);
		else
			j += ft_handle_words(g_data.input, j);
	}
	tmp_name = ft_substr(g_data.input, *i, (size_t)(j - *i));
	ft_new_token(tmp_name, WORD);
	free(tmp_name);
	tmp_name = NULL;
	*i = j;
	return (0);
}

int	ft_tokens_fill_list(void)
{
	int	i;

	i = 0;
	if (!g_data.input)
		return (-1);
	while (g_data.input[i])
	{
		if (process_redirects(&i))
		{
			i++;
			continue ;
		}
		else if (g_data.input[i] != ' ')
			process_word(&i);
		else
			i++;
		if (i + 1 > (int)ft_strlen(g_data.input))
			break ;
	}
	return (0);
}
