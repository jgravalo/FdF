#include "gnl/get_next_line.h"
#include "fdf.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h> 

int main(int argc, char **argv)
{
	int j;
	int i;

	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	char *c = get_next_line(fd);
	for (j = 0; c; j++)
	{
		c = ft_substr(c, 0, ft_strlen(c) - 1);
//		printf("line = %s\n", c);
		char **m = ft_split(c, ' ');
		printf("numbers = ");
		for (i = 0; m[i]; i++)
			printf("%s ", m[i]);
		printf("\n");
		c = get_next_line(fd);
	}
	printf("i = %d, j = %d\n", i , j);
	return (0);
}
