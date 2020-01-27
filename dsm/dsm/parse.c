/*
	parse
*/

#include "dsm.h"

void	check_magic_header(int fd)
{
	int tmp;

	read(fd, &tmp, 4);
	swap_32(&tmp);
	if (tmp != COREWAR_EXEC_MAGIC)
		exit(0);
}

int		valid_file(int argc, char **argv)
{
	int		i;

	i = 0;
	if (argc > 1)
	{
		while (argv[argc - 1][i])
		{
			if (argv[argc - 1][i] == '.' \
				&& argv[argc - 1][i  + 1] && argv[argc - 1][i + 1] == 'c' \
				&& argv[argc - 1][i  + 2] && argv[argc - 1][i + 2] == 'o' \
				&& argv[argc - 1][i  + 3] && argv[argc - 1][i + 3] == 'r')
				return (1);
			i++;
		}
		return (0);
	}
	return (0);
}

char	*get_str(int fd, int size)
{
	char *str;

	str = (char *)malloc(size + 1);
	read(fd, str, size);
	str[size] = 0;
	return (str);
}

void	skip_4bytes(int fd)
{
	int i;

	read(fd, &i, 4);
	if (i != 0)
		exit(0); //error
}

void	validate_size(int fd, int size)
{
	int i;

	read(fd, &i, 4);
	swap_32(&i);
	if (i != size && i > CHAMP_MAX_SIZE)
		exit(0); //error
}

void		read_file(t_dsm *dsm, int fd)
{
	int		size;

	size = lseek(fd, 0, SEEK_END) - (COMMENT_LENGTH + PROG_NAME_LENGTH + 16);
	lseek(fd, 0, SEEK_SET);
	check_magic_header(fd);
	dsm->name = get_str(fd, PROG_NAME_LENGTH);
	skip_4bytes(fd);
	validate_size(fd, size);
	dsm->comment = get_str(fd, COMMENT_LENGTH);
	skip_4bytes(fd);
	get_code(dsm, fd);
}

void	parse(t_dsm *dsm, int argc, char **argv)
{
	int		fd;

	if (valid_file(argc, argv))
	{
		fd = open(argv[argc - 1], O_RDONLY);
		if (fd > 2)
			read_file(dsm, fd);
		close(fd);
	}
	else
	{
		// error
		exit(0);
	}
}