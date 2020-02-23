/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:06:46 by wvenita           #+#    #+#             */
/*   Updated: 2019/04/08 20:22:57 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_dpow(double nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0 || nb == 0)
		return (0);
	return (nb * ft_dpow(nb, (power - 1)));
}