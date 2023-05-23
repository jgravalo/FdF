#include "../inc/fdf.h"

t_map	find_size(char *argv)
{
	int		j;
	int		i;
	int		fd;
	char	*c;
	char	**m;
	t_map	size;

	fd = open(argv, O_RDONLY);
	c = get_next_line(fd);
		printf("%s\n", c);// BORRAR
	m = ft_split(c, ' ');
	i = 0;
	while (m[i])
	{
//		printf("%s(%d) ", m[i], i);// BORRAR
		i++;
	}
//	printf("\n");// BORRAR
	j = 0;
	while (c)
	{
		c = get_next_line(fd);
		j++;
	}
	size.x = i;
	size.y = j;
	printf("i = %d, j = %d\n", i , j);// BORRAR
	close(fd);
	return (size);
}

void 	make_struct(t_point **p, t_map size, char *argv)
{
	int		i;
	int		j;
	char	*c;
	char	**m;
	int		fd;

	i = 0;
	fd = open(argv, O_RDONLY);
	while (i <= size.y)
	{
//		c = ft_substr(get_next_line(fd), 0, ft_strlen(c) - 1);
		c = get_next_line(fd);
//			printf("c = %s\n", c);// BORRAR
		if (!c)
			break ;
//		printf("size.x = %d\n", size.x);// BORRAR
//		printf("sizeof int = %lu\n", sizeof(int));// BORRAR
//		printf("sizeof t_point = %lu\n", sizeof(t_point));// BORRAR
		p[i] = (t_point *)malloc(sizeof(t_point) * (size.x + 1));
		m = ft_split(c, ' ');
//			printf("m = ");// BORRAR
		j = 0;
		while (j < size.x)
		{
//			printf("%s(%d) ", m[j], j);// BORRAR
			p[i][j].z = ft_atoi(m[j]);
//			printf("(%d) ", p[i][j].z);// BORRAR
			j++;
		}
//		printf("esta aqui\n");// BORRAR
//		printf("\n");// BORRAR
		i++;
	}
	close(fd);
}

void	print_values(t_point **p, t_map size)
{
	int i, j;

	j = 0;
	for (i = 0; i < size.y; i++)
	{
		j = 0;
		while (j < size.x)
		{
			printf("%d(%d), ", p[i][j].z, j);// BORRAR
			j++;
		}
		printf("\n");// BORRAR
	}
}
/*
int main(int argc, char **argv)
{
	t_map	size;
	t_point	**p;

	if (argc < 2)
		return (0);
	size = find_size(argv[1]);
	printf("x = %d, y = %d\n", size.x , size.y);
	p = (t_point **)malloc(sizeof(t_point *) * (size.y));
	make_struct(p, size, argv[1]);
//	print_values(p);
	return (0);
}
*/
