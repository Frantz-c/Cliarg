/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   user_functions.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 16:09:16 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 20:06:58 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "cliarg.h"
#include <stdarg.h>

extern void		cli_transfer_to(t_cli **a, ...)
{
	va_list		ap;
	void		*addr;

	va_start(ap, a);
	while (*a)
	{
		addr = va_arg(ap, void*);
		if ((*a)->type & INT_TYPE)
		{
			if ((*a)->max <= INT_MAX && (*a)->min >= INT_MIN)
				*((int*)addr) = (int)(*(*a)->value.plong);
			else
				*((long*)addr) = *(*a)->value.plong;
		}
		else if ((*a)->type & STRING_TYPE)
		{
			*((char**)addr) = (*a)->value.str;
			(*a)->value = NULL;
		}
		else
			*((double*)addr) = *(*a)->value.pfloat;
		a++;
	}
	va_end(ap);
}

extern void		cli_transfer_to_struct(t_cli **a, void *addr)
{
	int		offset;

	offset = 0;
	while (*a)
	{
		if ((*a)->type & INT_TYPE)
		{
			if ((*a)->max <= INT_MAX && (*a)->min >= INT_MIN)
			{
				if (offset != 0 && offset % sizeof(int))
					offset += sizeof(int) - (offset % sizeof(int));
				*((int*)(addr + offset)) = (int)(*(*a)->value.plong);
			}
			else
			{
				if (offset != 0 && offset % sizeof(long))
					offset += sizeof(long) - (offset % sizeof(long));
				*((long*)(addr + offset)) = *(*a)->value.plong;
			}
		}
		else if ((*a)->type & STRING_TYPE)
		{
			if (offset != 0 && offset % sizeof(char*))
				offset += sizeof(char*) - (offset % sizeof(char*));
			*((char**)(addr + offset)) = (*a)->value.str;
			(*a)->value = NULL;
		}
		else
		{
			if (offset != 0 && offset % sizeof(double))
				offset += sizeof(double) - (offset % sizeof(double));
			*((double*)(addr + offset)) = *(*a)->value.pfloat;
		}
		a++;
	}
}
