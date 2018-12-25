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

	new = malloc(sizeof(t_cli));
	new->value = NULL;
	new->type = 0;
	new->flag = 0;
	new->min = 0x8000000000000000L;
	new->max = 0x7fffffffffffffffL;
	new->len = 0;
	new->value_is_next_arg = 0;
	new->sname = NULL;
	new->lname = NULL;
	return (new);
}

t_cli	**cli_search_arguments(t_cli **arg, int ac, char **av)
{
	int		*checked;
	int		i;

	i = 0;
	checked = malloc(ac * sizeof(int));
	ft_memset(checked, '\0', ac * sizeof(int));
	while (arg[i])
	{
		if (arg[i]->lname)
            if (search_long_argument(arg[i], ac, av, checked) == CLI_ERROR)
                return (free_cli_and_return_null(arg));
        i++;
    }
	i = 0;
	while (arg[i])
	{
        if (arg[i]->sname && arg[i]->value_is_next_arg && arg[i]->value == NULL)
        {
            if (search_short_argument_next(arg[i], ac, av, checked) == CLI_ERROR)
                return (free_cli_and_return_null(arg));
        }
		i++;
	}
    i = 0;
	while (arg[i])
	{
        if (arg[i]->sname && !arg[i]->value_is_next_arg && arg[i]->value == NULL)
        {
            if (search_short_argument(arg[i], ac, av, checked) == CLI_ERROR)
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

void			set_argument_name(const char **fmt, t_cli *arg)
{
	const char	*s = *fmt;
	const char	*end = s;

	while (*end == '-')
		end++;
	end++;
	if (!ft_isalpha(*end))
	{
		arg->sname = ft_strndup(s, end - s);
		if (*end == '|')
		{
			s = ++end;
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

void			set_argument_type(const char *s, t_cli *arg)
{
	arg->type = cli_get_type(&s);
	if (*s == ':')
	{
		s++;
		arg->min = get_number(&s);
		if (*(++s) == ')')
			return ;
		arg->max = get_number(&s);
	}
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

extern t_cli	**cli_get_arguments(const char **fmt, int ac, char **av)
{
	const char	*argument;
	t_cli		**arg;
	int			i;

	i = 0;
	arg = malloc(sizeof(t_cli*) * (fmt_count(fmt) + 1));
	while (fmt[i])
	{
		argument = fmt[i];
		arg[i] = new_arg();
		arg[i]->value_is_next_arg = value_is_next(&argument);
		set_argument_name(&argument, arg[i]);
		if (*argument == '\0')
			arg[i]->type = BOOL_TYPE;
		else
			set_argument_type(argument + 1, arg[i]);
		printf(
			"{%d} sname = \"%s\"\n"
			"    lname = \"%s\"\n"
			"    value = \"%s\"\n"
			"    type  =   %#x\n"
			"    min   =   %ld\n"
			"    max   =   %ld\n"
			"    vina  =   %d\n\n",
			i, arg[i]->sname, arg[i]->lname, arg[i]->value,
			arg[i]->type, arg[i]->min, arg[i]->max, arg[i]->value_is_next_arg
		);
		i++;
	}
	arg[i] = NULL;
	if (duplicate_argument(ac, av) == CLI_ERROR)
		return (free_cli_and_return_null(arg));
	return (cli_search_arguments(arg, ac, av));
}
