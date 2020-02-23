/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:20:10 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/23 21:05:50 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putnb(t_printf *p)
{
	intmax_t	n;

	if (p->f & F_INTMAX)
		n = (p->f & F_DLR) ? (va_arg(p->dap, intmax_t))
							: (va_arg(p->ap, intmax_t));
	else if (p->f & F_SIZE_T)
		n = (p->f & F_DLR) ? ((intmax_t)va_arg(p->dap, size_t))
							: ((intmax_t)va_arg(p->ap, size_t));
	else if (p->f & F_LONG)
		n = (p->f & F_DLR) ? ((intmax_t)va_arg(p->dap, long))
							: ((intmax_t)va_arg(p->ap, long));
	else if (p->f & F_LONG2)
		n = (p->f & F_DLR) ? ((intmax_t)va_arg(p->dap, long long))
							: ((intmax_t)va_arg(p->ap, long long));
	else if (p->f & F_SHORT)
		n = (p->f & F_DLR) ? (intmax_t)((short)va_arg(p->dap, int))
							: (intmax_t)((short)va_arg(p->ap, int));
	else if (p->f & F_SHORT2)
		n = (p->f & F_DLR) ? (intmax_t)((char)va_arg(p->dap, int))
							: (intmax_t)((char)va_arg(p->ap, int));
	else
		n = (p->f & F_DLR) ? (intmax_t)va_arg(p->dap, int)
							: (intmax_t)va_arg(p->ap, int);
	itoa_printf(n, p, 0);
}

void	pf_putnb_base(int base, t_printf *p)
{
	uintmax_t	n;

	if (p->f & F_INTMAX)
		n = (p->f & F_DLR) ? (va_arg(p->dap, uintmax_t))
							: (va_arg(p->ap, uintmax_t));
	else if (p->f & F_SIZE_T)
		n = (p->f & F_DLR) ? ((uintmax_t)va_arg(p->dap, size_t))
							: ((uintmax_t)va_arg(p->ap, size_t));
	else if (p->f & F_LONG)
		n = (p->f & F_DLR) ? ((uintmax_t)va_arg(p->dap, unsigned long))
							: ((uintmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & F_LONG2)
		n = (p->f & F_DLR) ? ((uintmax_t)va_arg(p->dap, unsigned long long))
							: ((uintmax_t)va_arg(p->ap, unsigned long long));
	else if (p->f & F_SHORT)
		n = (p->f & F_DLR) ? (uintmax_t)((t_u16)va_arg(p->dap, int))
							: (uintmax_t)((t_u16)va_arg(p->ap, int));
	else if (p->f & F_SHORT2)
		n = (p->f & F_DLR) ? (uintmax_t)((t_u8)va_arg(p->dap, int))
							: (uintmax_t)((t_u8)va_arg(p->ap, int));
	else if (p->f & F_PNTR)
		n = (p->f & F_DLR) ? (uintmax_t)(va_arg(p->dap, void *))
							: (uintmax_t)(va_arg(p->ap, void *));
	else
		n = (p->f & F_DLR) ? (uintmax_t)va_arg(p->dap, t_u32)
							: (uintmax_t)va_arg(p->ap, t_u32);
	itoa_base_printf(n, base, p);
}

void	itoa_printf(intmax_t n, t_printf *p, int len)
{
	char		s[21];
	uintmax_t	tmp;

	tmp = n > 0 ? n : -n;
	(n == 0 && !(p->f & F_APR)) ? len++ : len;
	while (tmp && ++len)
		tmp /= 10;
	if ((p->f & F_APR) && p->f & F_ZERO && (n < 0 || p->f & F_PLUS || p->f & F_SPACE))
		p->print = ft_max(len, p->prec);
	else if ((p->f & F_APR) && p->prec < p->min_w)
		p->print = ft_max(len, p->prec);
	else if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) && p->f & F_ZERO && !(p->f & F_APR) && !(p->f & F_MINUS))
		p->print = ft_max(len, p->min_w);
	else if (p->min_w < p->prec && !(p->f & F_ZERO))
		p->print = ft_max(len, p->prec);
	else
		p->print = len;
	if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) && (p->min_w != p->print || len == p->print))
		++p->print;
	p->padding = (p->print > p->min_w) ? 0 : p->min_w - p->print;
	padding(p, 0);
	itoa_base_fill((n > 0 ? n : -n), 10, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->print);
	padding(p, 1);
}

void	itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;
	char		s[21];
	long		len;

	len = (n == 0 && !(p->f & F_APR)) ? 1 : 0;
	tmp = n;
	while (tmp && ++len)
		tmp /= b;
	tmp = (p->f & F_APR) ? ft_max(len, p->prec) : ft_max(len, p->min_w);
	p->print = ((p->f & F_ZERO && !(p->f & F_MINUS)) || (p->f & F_APR)) ? tmp : len;
	p->print = ft_max(p->prec, p->print);
	len = (p->print >= p->prec) ? 1 : 0;
	((p->f & F_HASH) && b == 8 && len) ? --p->min_w : 0;
	((p->f & F_HASH) && b == 8 && !n && (p->f & F_APR)) ? ++p->print : 0;
	((p->f & F_HASH) && b == 16 && n) ? p->min_w -= 2 : 0;
	((p->f & F_HASH) && p->f & F_PNTR && !n) ? p->min_w -= 2 : 0;
	p->padding = (p->print > p->min_w) ? 0 : p->min_w - p->print;
	padding(p, 0);
	if ((n || (p->f & F_PNTR)) && (p->f & F_HASH) && ((b == 8 && len) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & F_PNTR)) && (p->f & F_HASH) && b == 16)
		buffer(p, ((p->f & F_UPCASE) ? "X" : "x"), 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->print);
	padding(p, 1);
}

void	itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE], t_printf *p)
{
	int	len;

	if (tmp && !(p->f & F_PNTR) && (p->f & F_ZERO)
		&& (p->f & F_HASH) && b == 16 && p->print > 4
		&& p->print > p->prec && (p->print <= p->min_w + 2))
		p->print -= 2;
	((p->f & F_HASH) && p->f & F_PNTR && !tmp
			&& (p->f & F_ZERO)) ? p->print -= 2 : 0;
	len = p->print;
	if (len)
		p->c = (p->f & F_UPCASE) ? 55 : 87;
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
}
