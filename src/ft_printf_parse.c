/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:21:02 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/06 15:42:56 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void field_dollar(t_printf *p)
{
	int parametr;

	parametr = check_dollar(p->format) ? ft_atoi(p->format) : 0;
	if (!parametr)
		return;
	p->f |= (parametr > 0 ? F_DOLLAR : 0);
	va_copy(p->dap, p->map);
	while (--parametr)
		va_arg(p->dap, void *);
	while (*p->format != '$')
		++p->format;
	if (*p->format == '$')
		++p->format;
}

static void parse_flags(t_printf *p)
{
	while ((p->n = ft_strchri("# +-0*", *p->format, -1)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (p->f & F_ASTERIX)
	{
		p->f &= ~F_ASTERIX;
		if ((p->n = (int)va_arg(p->ap, int)) < 0)
		{
			p->n = -p->n;
			p->f |= F_MINUS;
		}
		if (!(p->f & F_APR))
			p->min_width = p->n;
		else
			p->precision = p->n;
	}
}

static void field_width_precision(t_printf *p)
{
	if (48 < *p->format && *p->format < 58)
	{
		p->min_width = MAX(1, ft_atoi(p->format));
		while (47 < *p->format && *p->format < 58)
			++p->format;
	}
	if (*p->format == '.')
	{
		++p->format;
		p->precision = MAX(ft_atoi(p->format), 0);
		while (47 < *p->format && *p->format < 58)
			++p->format;
		p->f |= F_APR;
	}
}

static void conversion_specifier(t_printf *p)
{
	p->c = *p->format;
	if (p->c == 's')
		(p->f & F_LONG || p->f & F_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (ft_strchr("dDi", p->c))
		pf_putnb(p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->ap, unsigned));
	else if (ft_strchr("oOuUbBxX", p->c))
		pf_putnb_base(ft_strchri_lu(".b..ou..x", p->c, -1) << 1, p);
	else if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p' && (p->f |= F_PNTR) && (p->f |= F_HASH))
		pf_putnb_base(16, p);
	else if (p->c == 'n')
		*va_arg(p->ap, int *) = p->len;
	else if (p->c == 'f' || p->c == 'F')
		pf_putdouble(p);
	else
		cs_not_found(p);
}

void parse_optionals(t_printf *p)
{
	p->f = 0;
	p->min_width = 0;
	p->precision = 0;
	field_dollar(p);
	parse_flags(p);
	field_width_precision(p);
	while (42)
	{
		if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? F_LONG2 : F_LONG;
		else if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? F_SHORT2 : F_SHORT;
		else if (*p->format == 'j')
			p->f |= F_INTMAX;
		else if (*p->format == 'z')
			p->f |= F_SIZE_T;
		else if (*p->format == 'L')
			p->f |= F_LONGD;
		else
			break;
		++p->format;
	}
	parse_flags(p);
	if (ft_strchr("CDSUOBXF", *p->format))
		p->f |= (ft_strchr("XF", *p->format)) ? F_UPCASE: F_LONG;
	conversion_specifier(p);
}