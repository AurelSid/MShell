/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:47:48 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/22 13:55:38 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_put_args(char ***split, char *args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (args[i])
	{
		j = i;
		while (args[j] && args[j] != ' ')
		{
			if (args[j] == '\'' || args[j] == '\"')
				j += ft_handle_quotes(args, i);
			else
				j += ft_handle_words(args, i);
		}
		if (args[i] == ' ')
			i++;
		else
		{
			(*split)[k] = ft_substr(args, i, j);
			i = j;
			k++;
		}
	}
}

int	ft_argscount(char *args)
{
	int	j;
	int	nbr;

	j = 0;
	nbr = 0;
	while (args[j])
	{
		while (args[j] && args[j] != ' ')
		{
			if (args[j] == '\'' || args[j] == '\"')
				j += ft_handle_quotes(args, j);
			else
				j += ft_handle_words(args, j);
		}
		if (args[j] == ' ')
			j++;
		nbr++;
	}
	return (nbr);
}

char	**ft_split_args(char *args)
{
	char	**split;
	int		args_nbr;

	args_nbr = ft_argscount(args);
	split = malloc(sizeof(char *) * (args_nbr + 1));
	if (!split)
		return (NULL);
	ft_put_args(&split, args);
	ft_trimloop(&split);
	return (split);
}
