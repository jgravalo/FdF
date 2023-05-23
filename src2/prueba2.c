#include "../inc/minilibx_macos/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_line_img(void *mlx, void *mlx_win, t_data img, t_point start, int sumx, int sumy, int lenx, int leny)
{
//	int nx = sumx;
//	int ny = sumy;
	int nx = 0;
	int ny = 0;
	while (nx <= lenx && nx >= -lenx && ny <= leny && ny >= -leny)
//	while (nx <= lenx - 1 && nx >= -lenx + 1 && ny <= leny - 1 && ny >= -leny + 1)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, start.x + nx, start.y + ny);
		nx += sumx;
		ny += sumy;
	}
}

void	my_map_creator(void *mlx, void *mlx_win, t_data img, t_point start, t_point map, int len)
{

	int i = 0;
	while (i < map.y)
	{
		int j = 0;
		my_line_img(mlx, mlx_win, img, start, -1, 1, map.x * len, map.x * len);
		t_point	ptr = start;
		while (j < map.x + 1)
		{
			my_line_img(mlx, mlx_win, img, ptr, 1, 1, len, len);
			ptr.x -= len;
			ptr.y += len;
			j++;
		}
		start.x += len;
		start.y += len;
		i++;
	}
	my_line_img(mlx, mlx_win, img, start, -1, 1, map.x * len, map.x * len);

}

void	my_centre(void *mlx, void *mlx_win, t_data img, t_point start, int len)
{
	my_line_img(mlx, mlx_win, img, start, 0, -1, 0, len);//arriba
	my_line_img(mlx, mlx_win, img, start, 0, 1, 0, len);//abajo
	my_line_img(mlx, mlx_win, img, start, 1, 0, len, 0);//derecha
	my_line_img(mlx, mlx_win, img, start, -1, 0, len, 0);//izquierda
}

int	main(void)
{
	void	*mlx;
	t_data	img;
	int		x = 1050;
	int		y = 680;
	void	*mlx_win;
	t_point	start;
	t_point	map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, x, y, "Hello world!");
	img.img = mlx_new_image(mlx, x, y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 1 / 10, 1 / 10, 0x00FF0000);
	start.x = x / 2;
	start.y = y / 2;
	map.x = 10;
	map.y = 5;
	mlx_put_image_to_window(mlx, mlx_win, img.img, start.x, start.y);
	my_centre(mlx, mlx_win, img, start, 10);
/*	
	my_line_img(mlx, mlx_win, img, start, 1, -1, 160, 160);
	my_line_img(mlx, mlx_win, img, start, 1, -10 / 3, 60, 60);
	my_line_img(mlx, mlx_win, img, start, 2, -1, 30, 30);
*/
//	my_line_img(mlx, mlx_win, img, start, -1, 1, 60, 60);
//	my_line_img(mlx, mlx_win, img, start, 1, 1, 60, 60);

	start.y -= (map.x + map.y) * 30 / 2;
	if (map.x > map.y)
		start.x += (map.x - map.y) * 30 / 2;
	else
		start.x -= (map.y - map.x) * 30 / 2;
	my_map_creator(mlx, mlx_win, img, start, map, 20);

	mlx_loop(mlx);
}

/*
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_loop(mlx);
}*/
