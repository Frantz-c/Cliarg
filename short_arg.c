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

static int		get_arg_short_bool(t_cli *cli, int ac, char **av, int checked[])
{
	int			i;
    char        c;

	i = 0;
    c = cli->sname[ft_strlen(cli->sname) - 1];
	while (i < ac)
	{
		if (!checked[i] && ft_strchr(av[i], c))
		{
			cli->value = ft_strdup("");
			return (1);
		}
		i++;
	}
	return (0);
}

static int		get_arg_short(t_cli *cli, int ac, char **av, int checked[])
{
	const int	slen = ft_strlen(cli->sname);
	int			i;

	i = 0;
	while (i < ac)
	{
		if (!checked[i] && !ft_strncmp(cli->sname, av[i], slen))
		{
			if (*(av[i] + slen) != '=')
			{
				set_cli_err(CLI_NO_VALUE, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
			cli->value = ft_strdup(av[i] + slen + 1);
			checked[i] = 1;
            set_arg_by_type(cli);
			return (1);
		}
		i++;
	}
	return (0);
}

// next arg (same as get_arg_long_next)
static int		get_arg_short_next(t_cli *cli, int ac, char **av, int checked[])
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!checked[i] && !ft_strcmp(cli->sname, av[i]))
		{
			if (i + 1 == ac)
			{
				set_cli_err(CLI_NO_VALUE, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
			cli->value = ft_strdup(av[i + 1]);
			checked[i] = 1;
            set_arg_by_type(cli);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**  pas de cumul (-a : -abc invalide)
*/
static int		get_arg_short_uniq_bool(t_cli *cli, int ac, char **av, int checked[])
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!checked[i] && !ft_strcmp(cli->sname, av[i]))
		{
			cli->value = ft_strdup("");
			checked[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

extern int     search_short_argument_next(t_cli *arg, int ac, char *av[], int checked[])
{
    int     error;

    error = 0;
    if (arg->type == BOOL_TYPE)
        error = get_arg_short_uniq_bool(arg, ac, av, checked);
    else
        error = get_arg_short_next(arg, ac, av, checked);
    return (error);
}

extern int     search_short_argument(t_cli *arg, int ac, char *av[], int checked[])
{
    int     error;

    error = 0;
    if (arg->type == BOOL_TYPE && !arg->value)
        error = get_arg_short_bool(arg, ac, av, checked);
    else
        error = get_arg_short(arg, ac, av, checked);
    return (error);
}
