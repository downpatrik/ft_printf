/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:20:17 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/06 15:43:21 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void color(t_printf *p)
{
	int len;

	p->printed = 5;
	len = 0;
	if (!ft_strncmp(p->format, "{red}", (len = 5)))
		buffer(p, PF_RED, p->printed);
	else if (!ft_strncmp(p->format, "{green}", (len = 7)))
		buffer(p, PF_GREEN, p->printed);
	else if (!ft_strncmp(p->format, "{yellow}", (len = 8)))
		buffer(p, PF_YELLOW, p->printed);
	else if (!ft_strncmp(p->format, "{blue}", (len = 6)))
		buffer(p, PF_BLUE, p->printed);
	else if (!ft_strncmp(p->format, "{purple}", (len = 8)))
		buffer(p, PF_PURPLE, p->printed);
	else if (!ft_strncmp(p->format, "{cyan}", (len = 6)))
		buffer(p, PF_CYAN, p->printed);
	else if (!ft_strncmp(p->format, "{eoc}", (len = 5)))
		buffer(p, PF_EOC, --p->printed);
	else if ((len = 1))
		buffer(p, p->format, 1);
	p->format += len - 1;
}

static void ldtoa_fill(long double n, t_printf *p, long value, int b)
{
	int len;
	char s[48];

	p->c = (p->f & F_UPCASE) ? 55 : 87;
	len = p->printed - 1 - p->precision;
	while (p->precision--)
	{
		s[len + p->precision + 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	(p->printed != (len + 2 + p->precision) || (p->f & F_HASH)) ? s[len] = '.' : p->precision--;
	value = ABS(n);
	while (++p->precision < len)
	{
		s[len - p->precision - 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	p->padding = MAX(0, (p->min_width - p->printed));
	padding(p, 0);
	buffer(p, s, p->printed);
	padding(p, 1);
}

void pf_putdouble(t_printf *p)
{
	long double n;
	long tmp;
	int len;
	long double decimal;

	if (p->f & F_LONG || p->f & F_LONGD)
		n = (p->f & F_DOLLAR) ? va_arg(p->dap, long double) : va_arg(p->ap, long double);
	else
		n = (p->f & F_DOLLAR) ? va_arg(p->dap, double) : va_arg(p->ap, double);
	if (!(p->f & F_APR))
		p->precision = 6;
	len = (p->f & F_PLUS || p->f & F_SPACE || n < 0) ? 2 : 1;
	tmp = ((long)n == 0) ? 1 : ((long)(DABS(n)));
	while (tmp && ++len)
		tmp /= 10;
	p->printed = p->precision + len;
	((p->f & F_APR) && p->precision == 0  && !(p->f & F_HASH)) ? p->printed-- : 0;
	p->printed = (p->printed < p->min_width && p->f & F_ZERO ) ? p->min_width : p->printed;
	decimal = (DABS(n) - (long)(DABS(n))) * ft_dpow(10, p->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	ldtoa_fill(n, p, (long)decimal, 10);
}

int check_dollar(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
		else if (ft_strchr("# +-0*.lhjzLipncCdDsSuUoObBxXfFgGeE%", str[i]))
			return (0);
	}
	return (0);
}