/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/18 16:04:05 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_redirects(int *i)
{
	if (ft_return_data()->input[*i] == '>')
	{
		if (ft_return_data()->input[*i + 1] == '>')
		{
			ft_new_token(">>", REDIRECT_APPEND);
			(*i)++;
		}
		else
			ft_new_token(">", REDIRECT_OUT);
	}
	else if (ft_return_data()->input[*i] == '<')
	{
		if (ft_return_data()->input[*i + 1] == '<')
		{
			ft_new_token("<<", REDIRECT_HEREDOC);
			(*i)++;
		}
		else
			ft_new_token("<", REDIRECT_IN);
	}
	else if (ft_return_data()->input[*i] == '|')
		ft_new_token("|", PIPE);
	else
		return (0);
	return (1);
}

int	process_word_utils(int *j)
{
	int	h;

	h = 0;
	if (ft_return_data()->input[*j] == '\''
		|| ft_return_data()->input[*j] == '\"')
	{
		h = ft_handle_quotes(ft_return_data()->input, *j);
		if (h != -1)
			*j += h;
		else
			return (-1);
	}
	else
		*j += ft_handle_words(ft_return_data()->input, *j);
	return (0);
}

int	process_word(int *i)
{
	int				j;
	char			*tmp_name;
	t_program_data	*tmp;

	j = *i;
	tmp = ft_return_data();
	while (tmp->input[j] && (tmp->input[j] != ' ' && tmp->input[j] != '>'
			&& tmp->input[j] != '<' && tmp->input[j] != '|'))
	{
		if (process_word_utils(&j) == -1)
			return (-1);
	}
	tmp_name = ft_substr(tmp->input, *i, (size_t)(j - *i));
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
	if (!ft_return_data()->input)
		return (-1);
	while (ft_return_data()->input[i])
	{
		if (process_redirects(&i))
		{
			i++;
			continue ;
		}
		else if (ft_return_data()->input[i] != ' ')
		{
			if (process_word(&i) == -1)
				return (-1);
		}
		else
			i++;
		if (i + 1 > (int)ft_strlen(ft_return_data()->input))
			break ;
	}
	return (0);
}
