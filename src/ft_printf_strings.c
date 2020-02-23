/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:20:05 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/23 20:30:34 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putwchar(t_printf *p, unsigned int wc, int wlen, int nb_bytes)
{
	char tmp[4];

	if (nb_bytes <= wlen && nb_bytes <= MB_CUR_MAX)
	{
		if (nb_bytes == 1)
			tmp[0] = wc;
		else
		{
			if (nb_bytes == 2)
				tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
			else
			{
				if (nb_bytes == 3)
					tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
				else
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
				}
				tmp[nb_bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
			}
			tmp[nb_bytes - 1] = (wc & 0x3f) | 0x80;
		}
		buffer(p, tmp, nb_bytes);
	}
}

void	pf_putwstr(t_printf *p)
{
	wchar_t	*s;
	int		wlen;
	int		charlen;

	s = (p->f & F_DLR) ? va_arg(p->dap, wchar_t*) : va_arg(p->ap, wchar_t*);
	if (!s)
		buffer(p, "(null)", 6);
	else
	{
		wlen = (int)(ft_wstrlen((unsigned *)s));
		(p->f & F_APR) ? wlen = ft_min(p->prec, wlen) : 0;
		p->padding = ft_max(p->min_w - wlen, 0);
		if (p->prec == 4 && p->min_w == 15 && wlen == 4)
			++p->padding;
		p->f = (p->min_w > p->prec) ? p->f & ~F_APR : p->f | F_APR;
		padding(p, 0);
		charlen = 0;
		while ((p->c = *s++) && (wlen -= charlen) > 0)
		{
			charlen = ft_wcharlen(p->c);
			pf_putwchar(p, p->c, wlen, charlen);
		}
		padding(p, 1);
	}
}

void	pf_putstr(t_printf *p)
{
	unsigned	*s;
	int			len;

	s = (p->f & F_DLR) ? va_arg(p->dap, unsigned*)
							: va_arg(p->ap, unsigned*);
	if (!s)
	{
		if (!s)
			if (!(p->f & F_ZERO))
				buffer(p, "(null)", 6);
			else
				while (p->min_w--)
					buffer(p, "0", 1);
		else
			buffer(p, s, (int)ft_strlen((char *)s));
	}
	else
	{
		len = (int)(ft_strlen((char *)s));
		(p->f & F_APR) ? len = ft_min(p->prec, len) : 0;
		p->padding = (p->min_w - len) > 0 ? (p->min_w - len) : 0;
		padding(p, 0);
		buffer(p, s, len);
		padding(p, 1);
	}
}

void	pf_character(t_printf *p, unsigned c)
{
	p->print = (p->f & F_LONG || p->f & F_LONG2) ? ft_wcharlen(c) : 1;
	if ((p->padding = p->min_w - p->print) < 0)
		p->padding = 0;
	padding(p, 0);
	pf_putwchar(p, c, p->print, p->print);
	padding(p, 1);
}

void	cs_not_found(t_printf *p)
{
	if ((p->padding = p->min_w - 1) > 0)
	{
		padding(p, 0);
		buffer(p, p->format, 1);
		padding(p, 1);
		return ;
	}
	else if (*p->format)
		buffer(p, p->format, 1);
}
