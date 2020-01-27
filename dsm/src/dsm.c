/*
	dessasembler
*/

#include "dsm.h"

void	swap_32(int *a)
{
	unsigned char	b;
	unsigned char	c;

	b = ((unsigned char *)a)[0];
	((unsigned char *)a)[0] = ((unsigned char *)a)[3];
	((unsigned char *)a)[3] = b;
	b = ((unsigned char *)a)[1];
	((unsigned char *)a)[1] = ((unsigned char *)a)[2];
	((unsigned char *)a)[2] = b;
}


void	swap_16(short *a)
{
	unsigned char	b;
	unsigned char	c;

	b = ((unsigned char *)a)[0];
	((unsigned char *)a)[0] = ((unsigned char *)a)[1];
	((unsigned char *)a)[1] = b;
}

int		dissassembler(int argc,char **argv)
{
	t_dsm	dsm;

	init_struct(&dsm);
	parse(&dsm, argc, argv);
	printf("here\n");
	creat_s_file(&dsm, argv[argc - 1]);
	return (1);
}


int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (dissassembler(argc, argv))
			return (1);
		else
			return (0);
	}
	return (0);
}