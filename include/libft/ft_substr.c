/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:38:08 by asideris          #+#    #+#             */
/*   Updated: 2024/10/10 16:16:27 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char *ft_substr(char const *s, unsigned int start, size_t len) {
    char *s2;

    if (!s) 
        return (NULL);

    if (start >= ft_strlen(s))
        return (ft_strdup(""));

    if (ft_strlen(s) - start < len)
        len = ft_strlen(s) - start;

    s2 = (char *)ft_calloc(len + 1, sizeof(char));
    if (!s2)
        return (NULL);

    ft_memcpy(s2, s + start, len);
    return (s2); 
}
