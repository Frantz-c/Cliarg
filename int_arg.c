/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   int_arg.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 08:54:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 20:07:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "cliarg.h"
#include <stdio.h>

int         is_numeric_string(const char *s)
{
    while (*s)
    {
       if (*s > '9' || *s < '0') 
        return (0);
        s++;
    }
    return (1);
}

extern void		set_int_arg_value(t_cli *cli)
{
	long	n;

	if (!is_numeric_string(cli->value))
	{
		cli->flag = CLI_INVALID_VALUE;
		ft_memset(cli->value, '\0', ft_strlen(cli->value));
		return;
	}
	n = ft_atol(cli->value);
	if (n > cli->max)
	{
		cli->flag = CLI_OVERFLOW_VALUE;
		ft_memset(cli->value, '\0', ft_strlen(cli->value));
	}
	else if (n < cli->min)
	{
		cli->flag = CLI_UNDERFLOW_VALUE;
		ft_memset(cli->value, '\0', ft_strlen(cli->value));
	}
	else
	{
		free(cli->value);
		cli->value = malloc(sizeof(long));
		*((long*)cli->value) = n;
	}
}
