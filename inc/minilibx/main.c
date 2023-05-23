#include<stdio.h>

void    *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);

// mlx_int_str_to_wordtab.c
int mlx_int_str_str(char *str,char *find,int len);

int mlx_int_str_str_cote(char *str,char *find,int len);

char    **mlx_int_str_to_wordtab(char *str);

// mlx_xpm.c
char    *mlx_int_get_line(char *ptr,int *pos,int size);

int mlx_int_get_col_name(char *str,int size);

int mlx_int_get_text_rgb(char *name, char *end);

int mlx_int_file_get_rid_comment(char *ptr, int size);


int main()
{
	t_xvar	*xvar;
	void 	*ptr = mlx_new_window(xvar, 105, 68, "Hola Mundo");
	/*
	char	*str = "Hola Mundo";
	char	**res = mlx_int_str_to_wordtab(str);
	int i;
	
	for (i = 0; res[i]; i++)
		printf("res[%d] = %s\n", i, res[i]);
	*/
	return 0;
}
