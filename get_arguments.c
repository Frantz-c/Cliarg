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

t_cli	**free_cli_and_return_null(t_cli **cli)
{
	t_cli	**start;

	start = cli;
	while (*cli)
	{
		if ((*cli)->sname)
			free((*cli)->sname);
		if ((*cli)->lname)
			free((*cli)->lname);
		if ((*cli)->value)
			free((*cli)->value);
		cli++;
	}
	free(start);
	return (NULL);
}

t_cli	*new_arg(void)
{
	t_cli	*new;

	new = (t_cli*)malloc(sizeof(t_cli));
	new->value = NULL;
	new->sname = NULL;
	new->lname = NULL;
	new->type = 0;
	new->flag = 0;
	new->min = 0x8000000000000000L;
	new->max = 0x7fffffffffffffffL;
	new->len = 0;
	new->value_is_next_arg = 0;
	new->traited = 0;
	return (new);
}

t_cli	**cli_search_arguments(t_cli **arg, int ac, char **av)
{
	int		    i;
    int         j;
    int         nlast;
    t_avstat    avstat;

	avstat.checked = malloc(ac * sizeof(int));
	ft_memset(avstat.checked, '\0', ac * sizeof(int));
    avstat.remaind = ac;

    // noprefix start
    i = 0;
    while (arg[i] && arg[i]->type & NOPREFIX)
        i++;
    if (i > 0) // pas assez d'arguments
    {
        j = 0;
        while (j < i)
        {
            if (j >= ac)
            {
                set_cli_err(CLI_TO_FEW_ARG, NULL); //ERROR
                free(avstat.checked);
                puts("\e[1;31mTO FEW ARGUMENTS\e[0m");
                return (arg);
            }
            arg[j]->value = ft_strdup(av[j]);
            avstat.checked[j] = 1;
            avstat.remaind--;
            set_arg_by_type(arg[j]);
            j++;
        }
    }

    // noprefix end
    while (arg[i] && !(arg[i]->type & NOPREFIX))
        i++;
    if (arg[i])
    {
        j = i;
        while (arg[j] && (arg[j]->type & NOPREFIX))
            j++;
        nlast = j - i;
        j = ac - nlast;
        if (j < 0)
        {
            set_cli_err(CLI_TO_FEW_ARG, NULL); //ERROR
            free(avstat.checked);
            puts("(2)\e[1;31mTO FEW ARGUMENTS\e[0m");
            return (arg);
        }
        while (nlast)
        {
            if (avstat.checked[j] == 0)
            {
                arg[i]->value = ft_strdup(av[j]);
                avstat.checked[j] = 1;
                avstat.remaind--;
                set_arg_by_type(arg[i]);
                i++;
            }
            nlast--;
            j++;
        }
    }

    i = 0;
	while (arg[i])
	{
		if (arg[i]->lname)
            if (search_long_argument(arg[i], ac, av, &avstat) == CLI_ERROR)
                return (free_cli_and_return_null(arg));
        i++;
    }
	i = 0;
	while (arg[i])
	{
        if (arg[i]->sname && arg[i]->value_is_next_arg && arg[i]->traited == 0)
        {
            if (search_short_argument_next(arg[i], ac, av, &avstat) == CLI_ERROR)
                return (free_cli_and_return_null(arg));
        }
		i++;
	}
    i = 0;
	while (arg[i])
	{
        if (arg[i]->sname && !arg[i]->value_is_next_arg && arg[i]->traited == 0)
        {
            if (search_short_argument(arg[i], ac, av, &avstat) == CLI_ERROR)
                return (free_cli_and_return_null(arg));
        }
		i++;
	}
	return (arg);
}


static int		fmt_count(const char **fmt)
{
	int		i;

	i = 0;
	while (fmt[i])
		i++;
	return (i);
}

int				value_is_next(const char **s)
{
	if (**s == '>')
	{
		(*s)++;
		return (1);
	}
	return (0);
}

void            get_noprefix_type(const char **fmt, t_cli *arg)
{
    int     type;

    (*fmt)++;
    type = cli_get_type(fmt);
        arg->type = type | NOPREFIX;
}

void			set_argument_name(const char **fmt, t_cli *arg)
{
	const char	*s = *fmt;
	const char	*end = *fmt;

    if (**fmt == '(')
        return ;
	while (*end == '-')
		end++;
	end++;
	if (!ft_isalpha(*end))
	{
		arg->sname = ft_strndup(s, end - s);
		if (*end == ',')
		{
            if (*(++end) == ' ')
                ++end;
			s = end;
			while (*end == '-')
				end++;
			while (ft_isalpha(*end))
				end++;
			arg->lname = ft_strndup(s, end - s);
		}
	}
	else
	{
		while (ft_isalpha(*end))
			end++;
		arg->lname = ft_strndup(s, end - s);
	}
	*fmt = end;
}

long			get_number(const char **s)
{
	t_ulong		n;
	int			sign;

	n = 0;
	if (**s == '-')
	{
		sign = 1;
		(*s)++;
	}
	else
		sign = 0;
	while (ft_isdigit(**s))
	{
		n *= 10;
		n += **s - 48;
		(*s)++;
	}
	return ((sign) ? ~n + 1 : n);
}

void			set_argument_type(const char **fmt, t_cli *arg)
{
	const char	*s = *fmt + 1;

    arg->type = cli_get_type(&s);
    if (!arg->lname && !arg->sname)
        arg->type |= NOPREFIX;
	if (*s == ':')
	{
		s++;
		arg->min = get_number(&s);
		if (*(++s) != ')')
			arg->max = get_number(&s);
	}
	*fmt = s + 1;
}

void			set_default_value(const char *fmt, t_cli *arg)
{
	if (*fmt == '\0')
		return ;
	if (*fmt == ' ')
		fmt++;
	fmt++;
	if (*fmt == ' ')
		fmt++;
	arg->value = ft_strdup(fmt);
    set_arg_by_type(arg);
}

int				duplicate_argument(int ac, char **av)
{
	int		i;

	while (ac)
	{
		ac--;
		i = ac;
		while (i)
		{
			i--;
			if (ft_strcmp(av[i], av[ac]) == 0)
			{
				set_cli_err(CLI_DUPLICATE_AV, ft_strdup(av[i]));
				return (CLI_ERROR);
			}
		}
	}
	return (0);
}

extern t_cli	**get_args_from_cli(const char **fmt, int ac, char **av)
{
	const char	*argument;
	t_cli		**arg;
	int			i;

    set_cli_err(0, NULL);
	arg = malloc(sizeof(t_cli*) * (fmt_count(fmt) + 1));
	i = 0;
	while (fmt[i])
	{
		argument = fmt[i];
		arg[i] = new_arg();
		arg[i]->value_is_next_arg = value_is_next(&argument);
		set_argument_name(&argument, arg[i]);
		if (*argument == '\0')
			arg[i]->type = BOOL_TYPE;
		else
		{
			set_argument_type(&argument, arg[i]);
			set_default_value(argument, arg[i]);
		}
		i++;
	}
	arg[i] = NULL;
	return (duplicate_argument(ac, av) == CLI_ERROR ?
		free_cli_and_return_null(arg) : cli_search_arguments(arg, ac, av));
}
