/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:20:10 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/06 15:43:07 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void pf_putnb(t_printf *p)
{
	intmax_t n;

	if (p->f & F_INTMAX)
		n = (p->f & F_DOLLAR) ? (va_arg(p->dap, intmax_t)) : (va_arg(p->ap, intmax_t));
	else if (p->f & F_SIZE_T)
		n = (p->f & F_DOLLAR) ? ((intmax_t)va_arg(p->dap, size_t))
													: ((intmax_t)va_arg(p->ap, size_t));
	else if (p->f & F_LONG)
		n = (p->f & F_DOLLAR) ? ((intmax_t)va_arg(p->dap, long))
													: ((intmax_t)va_arg(p->ap, long));
	else if (p->f & F_LONG2)
		n = (p->f & F_DOLLAR) ? ((intmax_t)va_arg(p->dap, long long))
													: ((intmax_t)va_arg(p->ap, long long));
	else if (p->f & F_SHORT)
		n = (p->f & F_DOLLAR) ? (intmax_t)((short)va_arg(p->dap, int))
													: (intmax_t)((short)va_arg(p->ap, int));
	else if (p->f & F_SHORT2)
		n = (p->f & F_DOLLAR) ? (intmax_t)((char)va_arg(p->dap, int))
													: (intmax_t)((char)va_arg(p->ap, int));
	else
		n = (p->f & F_DOLLAR) ? (intmax_t)va_arg(p->dap, int)
													: (intmax_t)va_arg(p->ap, int);
	itoa_printf(n, p, 0);
}

void pf_putnb_base(int base, t_printf *p)
{
	uintmax_t n;

	if (p->f & F_INTMAX)
		n = (p->f & F_DOLLAR) ? (va_arg(p->dap, uintmax_t)) : (va_arg(p->ap, uintmax_t));
	else if (p->f & F_SIZE_T)
		n = (p->f & F_DOLLAR) ? ((uintmax_t)va_arg(p->dap, size_t))
													: ((uintmax_t)va_arg(p->ap, size_t));
	else if (p->f & F_LONG)
		n = (p->f & F_DOLLAR) ? ((intmax_t)va_arg(p->dap, unsigned long))
													: ((intmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & F_LONG2)
		n = (p->f & F_DOLLAR) ? ((intmax_t)va_arg(p->dap, unsigned long long))
													: ((intmax_t)va_arg(p->ap, unsigned long long));
	else if (p->f & F_SHORT)
		n = (p->f & F_DOLLAR) ? (uintmax_t)((unsigned short)va_arg(p->dap, int))
													: (uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f & F_SHORT2)
		n = (p->f & F_DOLLAR) ? (uintmax_t)((unsigned char)va_arg(p->dap, int))
													: (uintmax_t)((unsigned char)va_arg(p->ap, int));
	else if (p->f & F_PNTR)
		n = (p->f & F_DOLLAR) ? (uintmax_t)(va_arg(p->dap, void *))
													: (uintmax_t)((va_arg(p->ap, void *)));
	else
		n = (p->f & F_DOLLAR) ? (uintmax_t)va_arg(p->dap, unsigned int)
													: (uintmax_t)va_arg(p->ap, unsigned int);
	itoa_base_printf(n, base, p);
}

void itoa_printf(intmax_t n, t_printf *p, int len)
{
	char s[21];
	uintmax_t tmp;

	tmp = ABS(n);
	(n == 0 && !(p->f & F_APR)) ? len++ : len;
	while (tmp && ++len)
		tmp /= 10;
	if((p->f & F_APR) &&  p->f & F_ZERO && (n < 0 || p->f & F_PLUS || p->f & F_SPACE))
		p->printed = MAX(len, p->precision);
	else if((p->f & F_APR) && p->precision < p->min_width)
		p->printed = MAX(len, p->precision);
	else if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) &&  p->f & F_ZERO && !(p->f & F_APR) && !(p->f & F_MINUS))
		p->printed = MAX(len, p->min_width);
	else if (p->min_width < p->precision && !(p->f & F_ZERO))
		p->printed = MAX(len, p->precision);
	else 
		p->printed = len;
	//printf("z%d %d %d %d %d\n", p->precision, p->min_width, p->printed, len, p->f & F_ZERO);
	if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) &&
			(p->min_width != p->printed || len == p->printed))
		++p->printed;
	p->padding = (p->printed > p->min_width) ? 0 : p->min_width - p->printed;
	padding(p, 0);
	itoa_base_fill(ABS(n), 10, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->printed);
	padding(p, 1);
}

void itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t tmp;
	char s[21];
	long len;

	len = (n == 0 && !(p->f & F_APR)) ? 1 : 0;
	tmp = n;
	while (tmp && ++len)
		tmp /= b;
	tmp = (p->f & F_APR) ? MAX(len, p->precision) : MAX(len, p->min_width);
	p->printed = ((p->f & F_ZERO && !(p->f & F_MINUS)) || (p->f & F_APR)) ? tmp : len;
	p->printed = MAX(p->precision, p->printed);
	len = (p->printed >= p->precision) ? 1 : 0;
	((p->f & F_HASH) && b == 8 && len) ? --p->min_width : 0;
	((p->f & F_HASH) && b == 8 && !n && (p->f & F_APR)) ? ++p->printed : 0;
	((p->f & F_HASH) && b == 16 && n) ? p->min_width -= 2 : 0;
	((p->f & F_HASH) && p->f & F_PNTR && !n) ? p->min_width -= 2 : 0;
	p->padding = (p->printed > p->min_width) ? 0 : p->min_width - p->printed;
	padding(p, 0);
	if ((n || (p->f & F_PNTR)) && (p->f & F_HASH) && ((b == 8 && len) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & F_PNTR)) && (p->f & F_HASH) && b == 16)
		buffer(p, ((p->f & F_UPCASE) ? "X" : "x"), 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->printed);
	padding(p, 1);
}

void itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE], t_printf *p)
{
	int len;
	if (tmp && !(p->f & F_PNTR) && (p->f & F_ZERO) && (p->f & F_HASH) && b == 16 &&
			p->printed > 4 && p->printed > p->precision && (p->printed <= p->min_width + 2))
		p->printed -= 2;
	((p->f & F_HASH) && p->f & F_PNTR && !tmp && (p->f & F_ZERO)) ? p->printed -= 2 : 0;
	len = p->printed;
	if (len)
		p->c = (p->f & F_UPCASE) ? 55 : 87;
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
}
