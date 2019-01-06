/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_arguments.c                                  .::    .:/ .      .::   */
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

extern void    set_arg_by_type(t_cli *arg)
{
    if (arg->type & INT_TYPE)
        set_int_arg_value(arg);
    else if (arg->type & STRING_TYPE)
        set_str_arg_value(arg);
    /*
    else if (arg->type & FLOAT_TYPE)
        set_float_value();
    */
}

extern int		cli_get_type(const char **s)
{
	static char	*type[5] = {
		"int", "float", "string", "str", "bool"
	};
	static int	length[5] = {
		3, 5, 6, 3, 4
	};
	static int	return_v[5] = {
		INT_TYPE, FLOAT_TYPE, STRING_TYPE, STRING_TYPE, BOOL_TYPE
	};
	int			i;

	i = 0;
	while (i < 5)
	{
		if (!ft_strncmp(*s, type[i], length[i]))
		{
			*s += length[i];
			return (return_v[i]);
		}
		i++;
	}
	return (CLI_ERROR);
}
