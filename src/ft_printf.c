/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sysadmin <Sysadmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:20:00 by Sysadmin          #+#    #+#             */
/*   Updated: 2020/02/05 20:52:41 by Sysadmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	t_printf p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.map, format);
	va_copy(p.ap, p.map);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format)
				break;
			parse_optionals(&p);
		}
		else if (*p.format == '{')
			color(&p);
		else
			buffer(&p, p.format, 1);
		(*p.format ? ++p.format : 0);
	}
	write(p.fd, p.buff, p.buffer_index);
	va_end(p.map);
	va_end(p.ap);
	va_end(p.dap);
	return (p.len);
}

int ft_dprintf(int fd, const char *format, ...)
{
	t_printf p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.map, format);
	va_copy(p.ap, p.map);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format)
				break;
			parse_optionals(&p);
		}
		else if (*p.format == '{')
			color(&p);
		else
			buffer(&p, p.format, 1);
		(*p.format ? ++p.format : 0);
	}
	write(p.fd, p.buff, p.buffer_index);
	va_end(p.map);
	va_end(p.ap);
	va_end(p.dap);
	return (p.len);
}

void buffer(t_printf *p, void *new, size_t size)
{
	int diff;
	long long new_i;

	new_i = 0;
	while ((PF_BUF_SIZE - p->buffer_index) < (int)size)
	{
		diff = PF_BUF_SIZE - p->buffer_index;
		ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		p->buffer_index += diff;
		p->len += diff;
		write(p->fd, p->buff, p->buffer_index);
		p->buffer_index = 0;
	}
	ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), size);
	p->buffer_index += size;
	p->len += size;
}

void padding(t_printf *p, int n)
{
	if (!p->padding)
		return;
	p->c = (p->f & F_ZERO) ? '0' : ' ';
	if(!(p->f & F_APR) && (p->f & F_ZERO) && n == 0)
		p->c = '0';
	else if ((p->precision < p->min_width) && (p->f & F_ZERO))
		p->c = ' ';
	if ((!n && !(p->f & F_MINUS)) || (n && (p->f & F_MINUS)))
		while (p->padding--)
			buffer(p, &p->c, 1);
}