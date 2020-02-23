/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:19:53 by wvenita           #+#    #+#             */
/*   Updated: 2019/04/17 23:08:18 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchri(char *s, int c, int i)
{
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

int		ft_strchri_lu(char *s, int c, int i)
{
	i = -1;
	while (s[++i])
		if (s[i] == c || s[i] == c + 32)
			return (i);
	return (-1);
}
