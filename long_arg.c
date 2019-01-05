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

static int		get_arg_long_bool(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	int			i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strcmp(cli->lname, av[i]))
		{
			cli->value = ft_strdup("");
			stat->checked[i] = 1;
            stat->remaind--;
			return (1);
		}
		i++;
	}
	return (0);
}

static int		get_arg_long(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	char		*eq_pos;
	const int	slen = ft_strlen(cli->lname);
	int			i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strncmp(cli->lname, av[i], slen))
		{
			if ((eq_pos = ft_strchr(av[i], '=')) == NULL)
			{
				set_cli_err(CLI_NO_VALUE, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
			cli->value = ft_strdup(eq_pos + 1);
			stat->checked[i] = 1;
            stat->remaind--;
            set_arg_by_type(cli);
			return (1);
		}
		i++;
	}
	return (0);
}

// next arg
static int		get_arg_long_next(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strcmp(cli->lname, av[i]))
		{
			if (i + 1 == ac)
			{
				set_cli_err(CLI_NO_VALUE, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
			cli->value = ft_strdup(av[i + 1]);
			stat->checked[i] = 1;
            stat->remaind--;
			return (1);
		}
		i++;
	}
	return (0);
}

static int		get_arg_long_next_bool(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strcmp(cli->lname, av[i]))
		{
			cli->value = ft_strdup("");
			stat->checked[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

extern int     search_long_argument(t_cli *arg, int ac, char *av[], t_avstat *stat)
{
    int     error;

    error = 0;
    if (arg->value_is_next_arg)
    {
        if (arg->type == BOOL_TYPE)
            error = get_arg_long_next_bool(arg, ac, av, stat);
        else
            error = get_arg_long_next(arg, ac, av, stat);
    }
    else
    {
        if (arg->type == BOOL_TYPE)
            error = get_arg_long_bool(arg, ac, av, stat);
        else
            error = get_arg_long(arg, ac, av, stat);
    }
    return (error);
}
