/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvenita <wvenita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 22:30:46 by wvenita           #+#    #+#             */
/*   Updated: 2020/02/23 20:30:34 by wvenita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <errno.h>

# include <stdio.h>

# define PF_RED "\033[31m"
# define PF_GREEN "\033[32m"
# define PF_YELLOW "\033[33m"
# define PF_BLUE "\033[34m"
# define PF_PURPLE "\033[35m"
# define PF_CYAN "\033[36m"
# define PF_EOC "\033[0m"

# define F_HASH 1
# define F_SPACE 2
# define F_PLUS 4
# define F_MINUS 8
# define F_ZERO 16
# define F_ASTERIX 32
# define F_UPCASE 64
# define F_SHORT 128
# define F_SHORT2 256
# define F_LONG 512
# define F_LONG2 1024
# define F_INTMAX 2048
# define F_SIZE_T 4096
# define F_DLR 8192
# define F_APR 16384
# define F_AW 32768
# define F_PNTR 65536
# define F_LONGD 131072

# define PF_BUF_SIZE 64

typedef struct	s_printf
{
	int			len;
	int			f;
	int			n;
	int			min_w;
	int			prec;
	int			padding;
	int			print;
	int			fd;
	int			buffer_index;
	char		buff[PF_BUF_SIZE];
	va_list		ap;
	va_list		dap;
	va_list		map;
	char		*format;
	unsigned	c;
}				t_printf;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

void			parse_optionals(t_printf *p);
void			cs_not_found(t_printf *p);

void			pf_putnb(t_printf *p);
void			pf_putnb_base(int base, t_printf *p);
void			itoa_printf(intmax_t d, t_printf *p, int len);
void			itoa_base_printf(uintmax_t d, int b, t_printf *p);
void			itoa_base_fill(uintmax_t tmp, int base, char *str, t_printf *p);

void			pf_putstr(t_printf *p);
void			pf_putwstr(t_printf *p);
void			pf_character(t_printf *p, unsigned c);
void			pf_putwchar(t_printf *p, unsigned int w, int wl, int n);

void			print_pointer_address(t_printf *p);
void			color(t_printf *p);
void			pf_putdouble(t_printf *p);
int				check_dollar(char *str);

void			buffer(t_printf *p, void *new_elem, size_t size);
void			buffer_flush(t_printf *p);

void			padding(t_printf *p, int n);

#endif
