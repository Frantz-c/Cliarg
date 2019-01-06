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

#include "libft.h"
#include "cliarg.h"

struct s_cli_error	g_cli_error;

/*
"-R--recursive(int:1,10+)"		= -R=[value] ou --recursive=[value]
">R|recursive(int:1,10+)"		= R [value] ou recursive=[value]
"-R|-recursive(int:1,10+)"		= -R=[...] ou -recursive=[...]
"-R|recursive(int:1,10+)"		= -R=[...] ou -recursive=[...]
">-R|--recursive(int:1,10+)"	= -R [value] ou --recursive [value]
*/

extern int		set_cli_err(int error, const char *arg)
{
	g_cli_error.error = error;
    if (arg)
        g_cli_error.arg = ft_strdup(arg);
    else
        g_cli_error.arg = NULL;
	return (CLI_ERROR);
}

#ifdef CLIARG_DEBUG

static void		cli_print_error(void)
{
	if (g_cli_error.error == CLI_INVALID_TYPE)
		printf("%s : invalid type\n", g_cli_error.arg);
	if (g_cli_error.error == CLI_INVALID_NAME)
		printf("%s : invalid name\n", g_cli_error.arg);
	/*
	if (g_cli_error.error == CLI_NO_VALUE)
		printf("%s : no value\n", g_cli_error.arg);
	*/
	if (g_cli_error.error == CLI_INVALID_DEFAULT)
		printf("%s : invalid default value\n", g_cli_error.arg);
	if (g_cli_error.error == CLI_INVALID_NOPRE_POS)
		puts("%s : no-prefix arguments must be in top or bottom");
}

static void		print_arguments(t_cli **arg)
{
	int		i;

	i = 0;
	while (*arg)
	{
        printf(
			"argument {%d} :\n    sname = \"%s\"\n    lname = \"%s\"\n"
			"    type  =   %d\n    min   =   %ld\n    max   =   %ld\n"
			"    next  =   %d\n",
			i++, (*arg)->sname, (*arg)->lname, (*arg)->type,
			(*arg)->min, (*arg)->max, (*arg)->value_is_next_arg
		);
		if ((*arg)->type & INT_TYPE)
			printf("    value = %ld\n\n", *((long*)(*arg)->value));
		else if ((*arg)->type & FLOAT_TYPE)
			printf("    value = %f\n\n", *((double*)(*arg)->value));
		else if ((*arg)->type & STRING_TYPE)
			printf("    value = \"%s\"\n\n", (char*)(*arg)->value);
		else
			printf("    value = %s\n\n", (*arg)->value ? "TRUE" : "FALSE");
        if ((*arg)->flag != 0)
            puts("\e[0;31mArgument not well formated\e[0m\n");
		arg++;
	}
}

extern t_cli	**get_args_from_cli_debug(const char **fmt, int ac, char **av)
{
	t_cli	**ret;

	if (invalid_fmt(fmt) == CLI_ERROR)
    {
        cli_print_error();
		return (NULL);
    }
	ret = get_args_from_cli(fmt, ac, av);
	print_arguments(ret);
	return (ret);
}

#endif

extern void		cli_argfree(t_cli **arg)
{
	t_cli	**ptr_array;

	ptr_array = arg;
	if (g_cli_error.arg)
		free(g_cli_error.arg);
	g_cli_error.error = 0;
	while (*arg)
	{
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
        "-f, --frantz(string) = une chaine",
        "-g(bool)",
        "-h(bool)",
        "-i(bool)",
        "(int:10,)",
		"(string:3,10)",
		NULL
	};

	t_cli **cli = get_args_from_cli_debug(args, argc - 1, argv + 1);
    if (cli == NULL)
        return (-1);
    printf("g_error = %d\n", g_cli_error.error);
	cli_argfree(cli);
	return (0);
}
