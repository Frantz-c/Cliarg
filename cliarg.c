/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cliarg.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 08:54:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 20:07:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft_clean/libft.h"
#include "cliarg.h"
#include <stdio.h>

struct s_cli_error	g_cli_error = {0, 0};

/*
"-R--recursive(int:1,10+)"		= -R=[value] ou --recursive=[value]
">R|recursive(int:1,10+)"		= R [value] ou recursive=[value]
"-R|-recursive(int:1,10+)"		= -R=[...] ou -recursive=[...]
"-R|recursive(int:1,10+)"		= -R=[...] ou -recursive=[...]
">-R|--recursive(int:1,10+)"	= -R [value] ou --recursive [value]
*/

extern void		cli_print_error(void)
{
	if (g_cli_error.error == CLI_INVALID_TYPE)
		printf("%s : invalid type\n", g_cli_error.arg);
	if (g_cli_error.error == CLI_INVALID_NAME)
		printf("%s : invalid name\n", g_cli_error.arg);
	if (g_cli_error.error == CLI_NO_VALUE)
		printf("%s : no value\n", g_cli_error.arg);
	if (g_cli_error.error == CLI_DUPLICATE_AV)
		printf("%s : duplicate argument (from cli)\n", g_cli_error.arg);
}

extern int		set_cli_err(int error, const char *arg)
{
	g_cli_error.error = error;
	g_cli_error.arg = ft_strdup(arg);
	return (CLI_ERROR);
}

#ifdef CLI_DEBUG_MODE

extern t_cli	**get_args_from_cli(const char **fmt, int ac, char **av)
{
	if (invalid_fmt(fmt) == CLI_ERROR)
		return (NULL);
	return (cli_get_arguments(fmt, ac, av));
}

#else

extern t_cli	**get_args_from_cli(const char **fmt, int ac, char **av)
{
	return (cli_get_arguments(fmt, ac, av));
}

#endif

extern void	cli_argfree(t_cli **arg)
{
	t_cli	**ptr_array;

	ptr_array = arg;
	if (g_cli_error.arg)
		free(g_cli_error.arg);
	g_cli_error.error = 0;
	while (*arg)
	{
		printf(
			"{??} sname = \"%s\"\n"
			"     lname = \"%s\"\n"
			"     value = \"%s\"\n"
			"     type  =   %d\n"
			"     min   =   %ld\n"
			"     max   =   %ld\n"
			"     vina  =   %d\n\n",
			(*arg)->sname, (*arg)->lname, (*arg)->value,
			(*arg)->type, (*arg)->min, (*arg)->max, (*arg)->value_is_next_arg
		);

		if ((*arg)->sname)
			free((*arg)->sname);
		if ((*arg)->lname)
			free((*arg)->lname);
		if ((*arg)->value)
			free((*arg)->value);
		free(*arg);
		arg++;
	}
	free(ptr_array);
}

int		main(int argc, char **argv)
{
	const char	*args[] = {
		">-l|--level(int:-1,5)",
		"-r|--recursive",
		"-integer(int:1,100)",
		NULL
	};

	t_cli **cli = get_args_from_cli(args, argc - 1, argv + 1);
	cli_print_error();
	cli_argfree(cli);
	return (0);
}
