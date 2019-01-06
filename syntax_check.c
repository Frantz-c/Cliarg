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

#ifdef CLIARG_DEBUG

#include "libft.h"
#include "cliarg.h"

static int		is_valid_name_prefix(const char **s)
{
	if (**s == '-')
	{
		(*s)++;
		if (**s == '-')
			(*s)++;
	}
	return (ft_isalpha(**s));
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
	return (1);
}

static int		verify_fmt_argument_type(const char **fmt)
{
	const char	*s = *fmt;
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
	if (*(s++) != ')')
		return (CLI_ERROR);
	*fmt = s;
	return (type);
}

static int		verify_fmt_default(const char *s, int type)
{
	if (*s == ' ')
		s++;
	if (*s == '=')
		s++;
	else
		return (CLI_ERROR);
	if (*s == ' ')
		s++;
	if (type == INT_TYPE)
	{
		if (!ft_isnumeric(s))
			return (CLI_ERROR);
	}
	else if (type == BOOL_TYPE)
		return (CLI_ERROR);
	else if (type == FLOAT_TYPE)
		return (0);
	return (0);
}

extern int		invalid_fmt(const char **fmt)
{
	const char	*argument;
	int			i;
	int			type;
	int			prefix;

	/*
	   if (verify_noprefix_args_position(fmt) == CLI_ERROR)
	   return (set_cli_err(CLI_INVALID_NOPRE_POS, NULL));
	 */
	i = 0;
	while ((argument = fmt[i]))
	{
		if (*argument == '\0')
			return (set_cli_err(CLI_INVALID_NAME, fmt[i]));
		if (!strcmp(argument, "(bool)"))
			return (set_cli_err(CLI_INVALID_TYPE, fmt[i]));
		if ((prefix = verify_fmt_argument_name(&argument)) == CLI_ERROR)
			return (set_cli_err(CLI_INVALID_NAME, fmt[i]));
		if (*argument != '\0' &&
				(type = verify_fmt_argument_type(&argument)) == CLI_ERROR)
			return (set_cli_err(CLI_INVALID_TYPE, fmt[i]));
		if (*argument != '\0' && !prefix &&
				verify_fmt_default(argument, type) == CLI_ERROR)
			return (set_cli_err(CLI_INVALID_DEFAULT, fmt[i]));
		i++;
	}
	return (0);
}

#endif
