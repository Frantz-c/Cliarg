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

extern void		set_int_arg_value(t_cli *cli)
{
	long	n;

	if (!ft_isnumeric(cli->value.str))
	{
		cli->error = CLI_INVALID_VALUE;
		free(cli->value.ptr);
		cli->value.ptr = NULL;
		return ;
	}
	n = ft_atol(cli->value.str);
	if (n > cli->max)
		cli->error = CLI_OVERFLOW_VALUE;
	else if (n < cli->min)
		cli->error = CLI_UNDERFLOW_VALUE;
	free(cli->value.ptr);
	cli->value.ptr = malloc(sizeof(long));
	*cli->value.plong = n;
}
