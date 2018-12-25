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
    if (arg->type == INT_TYPE)
        set_int_arg_value(arg);
    else if (arg->type == STRING_TYPE)
        set_str_arg_value(arg);
    /*
    else if (arg->type == FLOAT_TYPE)
        set_float_value();
    */
}
