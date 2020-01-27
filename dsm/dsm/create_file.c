/*
	create file
*/

#include "dsm.h"

void	print_shit(t_dsm *data)
{
	t_ops	*curr;
	t_args	*a;
	int		i;

	curr = data->operations;
	while (curr)
	{
		a = curr->args;
		i = 0;
		printf("%s\t", g_op_tab[curr->op_code].name);
		while (i < curr->nb_args)
		{
			if (a[i].arg_type == T_REG)
				printf("r%d", a[i].arg_value);
			if (a[i].arg_type == T_DIR)
				printf("%%%d", a[i].arg_value);
			if (a[i].arg_type == T_IND)
				printf("%d", a[i].arg_value);
			if (i < curr->nb_args - 1)
				printf(", ");
			i++;
			if (i == curr->nb_args)
				printf("\n");
		}
		curr = curr->next;
	}
}
void	creat_s_file(t_dsm *dsm, char *cor_name)
{
	print_shit(dsm);
}