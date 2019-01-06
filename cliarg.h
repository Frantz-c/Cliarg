/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cliarg.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 15:53:08 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 19:20:31 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "libft.h"
# include <stdio.h>
# include <string.h>

struct	s_avstat
{
    int		*checked;
    int		remaind;
};

typedef struct s_avstat	t_avstat;

struct	s_cli_error
{
	char	*arg;
	int		error;
};

union	u_alltype
{
	void	*ptr;
	long	*plong;
	double	*pfloat;
	char	*str;
};

struct	s_clistat
{
	int		plus : 1;
	int		traited : 1;
	int		valnextarg : 1;
};

typedef struct s_cli	t_cli;

struct	s_cli
{
	char				*sname;
	char				*lname;
	union u_alltype		value;
	int					type;				// INT_TYPE, ...
	int					len;				// uniquement si option '+'
	long				min;				// private
	long				max;				// private
	struct s_clistat	stat;				// CLI_PLUS, CLI_TRAITED, CLI_VNEXTARG
	int					error;				// overflow, underflow, invalid, ...
};

# define CLI_ERROR				-1
# define CLI_INVALID_NAME		1
# define CLI_INVALID_TYPE		2
# define CLI_NO_VALUE			3
# define CLI_DUPLICATE_AV		4
# define CLI_TO_FEW_ARG			5
# define CLI_TO_MANY_ARG		6
# define CLI_INVALID_DEFAULT	7
# define CLI_INVALID_NOPRE_POS	8

/*
** status values
*/
# define CLI_PLUS				0x1
# define CLI_TRAITED			0x2
# define CLI_VNA				0x4 // Value is Next Arg

/* 
** error values
*/
# define CLI_INVALID_VALUE       0x1
# define CLI_OVERFLOW_VALUE      0x2
# define CLI_UNDERFLOW_VALUE     0x4

/*
** types values
*/
# define INT_TYPE				0x01
# define FLOAT_TYPE				0x02
# define STRING_TYPE				0x04
# define BOOL_TYPE				0x08
# define INTA_TYPE				0x10
# define FLOATA_TYPE				0x20
# define STRA_TYPE				0x40
# define NOPREFIX_STR            0x104
# define NOPREFIX_INT            0x101
# define NOPREFIX_FLO            0x102
# define NOPREFIX_STRA			0x140
# define NOPREFIX_INTA			0x110
# define NOPREFIX_FLOATA			0x120
# define NOPREFIX                0x100

extern int		invalid_fmt(const char **fmt);
extern int		cli_get_type(const char **s);
extern int		set_cli_err(int error, const char *arg);
extern t_cli	**get_args_from_cli(const char **fmt, int ac, char **av);
extern int		search_long_argument(t_cli *arg, int ac,
									char *av[], t_avstat *stat);
extern void		set_str_arg_value(t_cli *cli);
extern void		set_int_arg_value(t_cli *cli);
extern void		set_arg_by_type(t_cli *arg);
extern int		search_short_argument_next(t_cli *arg, int ac,
											char *av[], t_avstat *stat);
extern int		search_short_argument(t_cli *arg, int ac,
										char *av[], t_avstat *stat);

extern struct s_cli_error	g_cli_error;
