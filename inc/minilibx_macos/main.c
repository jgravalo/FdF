#include<stdio.h>

char	**mlx_int_str_to_wordtab(char *str);

int main()
{
	char	*str = "Hola Mundo";
	char	**res = mlx_int_str_to_wordtab(str);
	int i;
	
	for (i = 0; res[i]; i++)
		printf("res[%d] = %s\n", i, res[i]);
	return 0;
}
