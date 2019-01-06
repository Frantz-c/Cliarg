/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string_arg.c                                     .::    .:/ .      .::   */
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

extern void        set_str_arg_value(t_cli *cli)
{
	const int	length = ft_strlen(cli->value.str);

	if (length < cli->min)
		cli->error = CLI_UNDERFLOW_VALUE;
	else if (length > cli->max)
		cli->error = CLI_OVERFLOW_VALUE;
}
