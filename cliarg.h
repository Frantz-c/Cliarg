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

# include "../libft_clean/libft.h"
# include <stdio.h>

struct	s_cli_error
{
	char	*arg;
	int		error;
};

typedef struct s_cli	t_cli;

struct	s_cli
{
	char	*sname;
	char	*lname;
	void	*value;
	int		type;				// INT_TYPE, ...
	int		len;				// uniquement si option '+'
	long	min;				// private
	long	max;				// private
	int		value_is_next_arg;	// private
	int		plus;				// private
};

#define CLI_ERROR				-1
#define CLI_INVALID_NAME		1
#define CLI_INVALID_TYPE		2
#define CLI_NO_VALUE			3
#define CLI_DUPLICATE_AV		4

#define INT_TYPE				0x1
#define FLOAT_TYPE				0x2
#define STRING_TYPE				0x4
#define BOOL_TYPE				0x8

extern int		invalid_fmt(const char **fmt);
extern int		cli_get_type(const char **s);
extern void		cli_print_error(void);
extern int		set_cli_err(int error, const char *arg);
extern t_cli	**cli_get_arguments(const char **fmt, int ac, char **av);

extern struct s_cli_error	g_cli_error;
