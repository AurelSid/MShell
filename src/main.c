/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/03 16:41:13 by roko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(int start, int end, const char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * (end - start) + 1);
	if (!s2)
		return (NULL);
	i = start;
	while (i < end - start)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
int	ft_handle_quotes(char type, t_program_data *data, int index)
{
	int	i;

	i = index;
	while (i < (int)ft_strlen(data->input) && data->input[i] != type)
		i++;
	if (i >= (int)ft_strlen(data->input))
		return (printf("ERROR"));
	return (i);
}

int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < (int)ft_strlen(data->input))
	{
		if (data->input[i] == '>')
		{
			if (data->input[i + 1] == '>')
			{
				ft_new_token(">>", data);
				i++;
			}
			else
				ft_new_token(">", data);
		}
		else if (data->input[i] == '<')
		{
			if (data->input[i + 1] == '<')
			{
				ft_new_token("<<", data);
				i++;
			}
			else
				ft_new_token("<", data);
		}
		else if (data->input[i] == '|')
			ft_new_token("|", data);
		else if (data->input[i] == '"')
		{
			j = i;
			i = ft_handle_quotes('"', data, i);
			ft_new_token(ft_strndup(j, i, data->input), data);
		}
		printf("char checked\n");
		i++;
	}
	return (0);
}
int	main(int argc, char **argv)
{
	char			*rl;
	t_program_data	data;

	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	rl = readline("$> ");
	data.input = rl;
	ft_tokens_fill_list(&data);
	printf("Printing tokens...");
	ft_print_tokens_list(data);
	return (0);
}
