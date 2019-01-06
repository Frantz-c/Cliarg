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

static int		get_arg_short_bool(t_cli *cli, int ac, char **av, t_avstat *stat)
{
    const int   len = ft_strlen(cli->sname) - 1;
	int			i;
    char        prefix[3];
    char        c;

	i = 0;
    c = cli->sname[len];
    if (len == 0)
        prefix[0] = '\0';
    else
        ft_strncpy(prefix, cli->sname, len);
	while (i < ac)
	{
        if (!stat->checked[i] && (!prefix[0] || !ft_strncmp(av[i], prefix, len))
            && ft_strchr(av[i], c))
		{
			cli->value = ft_strdup("");
			return (1);
		}
		i++;
	}
	return (0);
}

static int		get_arg_short(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	const int	slen = ft_strlen(cli->sname);
	int			i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strncmp(cli->sname, av[i], slen))
		{
			if (*(av[i] + slen) != '=')
			{
				set_cli_err(CLI_NO_VALUE, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
			if (cli->value)
				free(cli->value);
			cli->value = ft_strdup(av[i] + slen + 1);
			stat->checked[i] = 1;
            stat->remaind--;
            set_arg_by_type(cli);
			return (1);
		}
		i++;
	}
	return (0);
}

// next arg (same as get_arg_long_next)
static int		get_arg_short_next(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strcmp(cli->sname, av[i]))
		{
			if (i + 1 == ac)
				return (set_cli_err(CLI_NO_VALUE, ft_strdup(av[i])));
			if (cli->value)
				free(cli->value);
			cli->value = ft_strdup(av[i + 1]);
			stat->checked[i] = 1;
            stat->remaind--;
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
static int		get_arg_short_uniq_bool(t_cli *cli, int ac, char **av, t_avstat *stat)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (!stat->checked[i] && !ft_strcmp(cli->sname, av[i]))
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

extern int     search_short_argument_next(t_cli *arg, int ac, char *av[], t_avstat *stat)
{
    int     error;

    error = 0;
    if (arg->type == BOOL_TYPE)
        error = get_arg_short_uniq_bool(arg, ac, av, stat);
    else
        error = get_arg_short_next(arg, ac, av, stat);
    return (error);
}

extern int     search_short_argument(t_cli *arg, int ac, char *av[], t_avstat *stat)
{
    int     error;

    error = 0;
    if (arg->type == BOOL_TYPE)
        error = get_arg_short_bool(arg, ac, av, stat);
    else
        error = get_arg_short(arg, ac, av, stat);
    return (error);
}
