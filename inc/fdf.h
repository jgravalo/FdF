#ifndef FDF_H
#define FDF_H
#include "minilibx_macos/mlx.h"
#include "hooks.h"
#include "../gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define MPI 3.1415926535897932384

typedef struct	s_point{
	float	x;
	float	y;
	float	z;
	unsigned long	color;
	int	size;
	float	pos_x;
	float	pos_y;
}	t_point;

typedef struct	s_map{
	float			x;
	float			y;
	float			space;
	float			start_x;
	float			start_y;
}	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_var{
	void			*mlx;
	void			*win;
	t_data			img;
	t_map			size;
	float			x;
	float			y;
}	t_var;

typedef struct	s_line {
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		lenx;
	int		leny;
	float	sumx;
	float	sumy;
}	t_line;

unsigned long	ft_atoill(char *s);

void    free_fdf(t_point **fdf);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

int		key_hook(int keycode, t_var *vars);

int		close_win(int keycode, t_var *vars);

void	print_values(t_point **p, t_map size);

void	my_point(t_var *vars, int x, int y, int color);

t_point	**make_struct(int argc, char **argv, t_var *vars);

t_map	make_size(int argc, char **argv, t_var *vars);

void	print_struct(t_var *vars, t_point **fdf);

#endif