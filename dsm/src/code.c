/*
	code
*/

#include "dsm.h"

int	read_dir(int fd, t_ops *op, int arg_nbr)
{

	short		short_i;
	int			int_i;

	op->args[arg_nbr].arg_type = 2;
	if (g_op_tab[op->op_code].carry_b == 1)
	{
		read(fd, &short_i, 2);
		swap_16(&short_i);
		return ((int)short_i);
	}
	else
	{
		read(fd, &int_i, 4);
		swap_32(&int_i);
		return ((int)int_i);

	}
}

int		read_ind(int fd, t_ops *op, int arg_nbr)
{
	short		short_i;

	op->args[arg_nbr].arg_type = T_IND;
	read(fd, &short_i, 2);
	swap_16(&short_i);
	return ((int)short_i);
}

void	get_args(int fd, t_ops *op, unsigned char encoding_byte)
{
	int		i;
	int		arg_nbr;
	int		shift;

	i = 3;
	arg_nbr = 0;
	while (i + op->nb_args > 3)
	{
		shift = encoding_byte >> i * 2;
		if ((shift & 3) == 1)
		{
			op->args[arg_nbr].arg_type = 1;
			read(fd, &op->args[arg_nbr].arg_value, 1);
		}
		else if ((shift & 3) == 2)
			op->args[arg_nbr].arg_value = read_dir(fd, op, arg_nbr);
		else if ((shift & 3) == 3)
		{
			op->args[arg_nbr].arg_value = read_ind(fd, op, arg_nbr);
		}
		arg_nbr++;
		i--;
	}
}

t_ops	*new_operation(unsigned char op_code)
{
	t_ops	*new;

	new = (t_ops *)malloc(sizeof(t_ops));
	bzero(new, sizeof(t_ops));
	new->op_code = (int)op_code;
	new->nb_args = g_op_tab[op_code].n_args;
	new->args = (t_args *)malloc(sizeof(t_args) * new->nb_args);
	new->next = 0;
}

void	add_op(t_dsm *dsm, t_ops *op)
{
	t_ops	*tmp;

	if (!dsm->operations)
	{
		dsm->operations = op;
		return;
	}
	tmp = dsm->operations;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = op;
}

void	get_code(t_dsm *dsm, int fd)
{
	unsigned char	op_code;
	unsigned char	encoding_byte;
	t_ops			*op;

	while (read(fd, &op_code, 1))
	{
		op = new_operation(op_code);
		if (op_code > 0 && g_op_tab[op_code].carry_a)
		{
			read(fd, &encoding_byte, 1);
			get_args(fd, op, encoding_byte);

		}
		else
			op->args[0].arg_value = read_dir(fd, op, 0);
		add_op(dsm, op);
		op = 0;
	}
}