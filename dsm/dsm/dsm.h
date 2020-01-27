#ifndef DSM_H
# define DSM_H
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>


typedef struct	s_args
{
	int				arg_type;
	int				arg_value;
}				t_args;

typedef struct	s_ops
{
	int				op_code;
	int				nb_args;
	t_args			*args;
	struct s_ops	*next;
}				t_ops;


typedef struct	s_dsm
{
	char			*byte_code;
	char			*name;
	char			*comment;
	t_ops			*operations;
}				t_dsm;

/*
		init_struct
*/

void	init_struct(t_dsm *dsm);

void	parse(t_dsm *dsm, int argc, char **argv);

void	swap_32(int *a);
void	swap_16(short *a);

void	get_code(t_dsm *dsm, int fd);

void	creat_s_file(t_dsm *dsm, char *cor_name);


/*

*/

#endif