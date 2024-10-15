/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/15 16:08:53 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_words(t_program_data *data, int index)
{
	int	i;

	i = index;
	while (data->input[i] && (data->input[i] != ' '
			&& data->input[i] != '\'' && data->input[i] != '\"'))
		i++;
	return (i - index);
}

int	ft_handle_quotes(char type, t_program_data *data, int index)
{
	int	i;

	i = index;
	i++;
	while (data->input[i] != type && data->input[i])
		i++;
	i++;
	if (i > (int)ft_strlen(data->input))
		return (-1);
	/*  ---> no error but skip the command */
	return (i - index);
}

int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;
	int	j;

	if (!data || !data->input)
		return (-1);
	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '>')
		{
			if (data->input[i + 1] && data->input[i + 1] == '>')
			{
				ft_new_token(">>", data, REDIRECT_APPEND);
				i++;
			}
			else
				ft_new_token(">", data, REDIRECT_OUT);
		}
		else if (data->input[i] == '<')
		{
			if (data->input[i + 1] && data->input[i + 1] == '<')
			{
				ft_new_token("<<", data, REDIRECT_HEREDOC);
				i++;
			}
			else
				ft_new_token("<", data, REDIRECT_IN);
		}
		else if (data->input[i] == '|')
			ft_new_token("|", data, PIPE);
		else if (data->input[i] != ' ')
		{
			j = i;
			while (data->input[j] && data->input[j] != ' ')
			{
				if (data->input[j] == '\'' || data->input[j] == '\"')
					j += ft_handle_quotes(data->input[j], data, j);
				else
					j += ft_handle_words(data, j);
				// if (len < 0 || j > (int)ft_strlen(data->input))
				// 	return (-1);
			}
			ft_new_token(ft_substr(data->input, i, (size_t)j), data, WORD);
			i += j;
		}
		if (i + 1 > (int)ft_strlen(data->input))
			break ;
		i++;
	}
	return (0);
}

