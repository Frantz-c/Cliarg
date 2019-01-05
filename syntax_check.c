/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   syntax_check.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 15:45:24 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 17:27:30 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "cliarg.h"

static int		is_valid_name_prefix(const char **s)
{
	while (!ft_isalpha(**s) && **s == '-')
		(*s)++;
	return (ft_isalpha(**s));
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


static int		verify_fmt_argument_name(const char **fmt)
{
	const char	*s = *fmt;

	if (*s == '>')
		s++;
    else if (*s == '(')
        return (0);
	if (!*s || !is_valid_name_prefix(&s) || !*(++s))
		return (CLI_ERROR);
	if (ft_isalpha(*s)) //Pas d'argument court
	{
		while (ft_isalpha(*s) || (*s == '-' && ft_isalpha(s[1])))
			s++;
	}
	else if (*s == ',') //Argument court. argument long ?
	{
        if (*(s + 1) == ' ')
            s++;
		if (!*(++s) || !is_valid_name_prefix(&s))
			return (CLI_ERROR);
		while (ft_isalpha(*(++s))) //Argument long
			;
	}
	*fmt = s;
	return (0);
}

static int		verify_fmt_argument_type(const char *s)
{
	int			type;

	if (*(s++) != '(')
        return (*s == '\0') ? 0 : CLI_ERROR;
	if ((type = cli_get_type(&s)) == CLI_ERROR)
		return (CLI_ERROR);
	if (*s == ':')
	{
		if (*(++s) == '-' || *s == '+')
			s++;
		while (*s && ft_isdigit(*s))
			s++;
		if (!*s || *s != ',')
			return (CLI_ERROR);
		if (*(++s) == '-' || *s == '+')
			s++;
		while (*s && ft_isdigit(*s))
			s++;
	}
	if (*(s++) != ')' || *s)
		return (CLI_ERROR);
	return (0);
}

extern int		invalid_fmt(const char **fmt)
{
	const char	*argument;
	int			i;

	i = 0;
	while (fmt[i])
	{
		argument = fmt[i];
        if (*argument == '\0')
            return (set_cli_err(CLI_INVALID_NAME, fmt[i]));
        if (!strcmp(argument, "(bool)"))
			return (set_cli_err(CLI_INVALID_TYPE, fmt[i]));
		if (verify_fmt_argument_name(&argument) == CLI_ERROR)
			return (set_cli_err(CLI_INVALID_NAME, fmt[i]));
		if (*argument != '\0' &&
			verify_fmt_argument_type(argument) == CLI_ERROR)
			return (set_cli_err(CLI_INVALID_TYPE, fmt[i]));
		i++;
	}
	return (0);
}
